#ifndef _RNETW_SR_SENDER_HPP_
#define _RNETW_SR_SENDER_HPP_

#include "RdtSender.h"
#include "Global.h"
#include "../lib/rlog.hpp"
#include <cstdint>
#include <cassert>
#include <vector>
#include <queue>

class SRSender final : public RdtSender {
    using pkt_seq_t = decltype(Packet::seqnum);
public:
    SRSender(const pkt_seq_t windowSize) : windowSize(windowSize), cache(windowSize) {
        //! You are smart enough to know what I'm doing here.
        assert(windowSize * 2 > windowSize);
    }
    virtual bool send(Message &msg) override {
        if(!send_impl(msg))
            queuedMessages.push(msg);
        return true;
    }
    bool send_impl(Message &msg) {
        if(confirmedSeq + windowSize <= maxSeqOnUse) {
            //! The cache is full! Message must be queued and wait.
            return false;
        }
        else {
            //! The window is not full. Send the message.
            ++maxSeqOnUse;
            auto m_seq = maxSeqOnUse;
            auto m_index = m_seq % windowSize;

            Packet &m_pkt = cache[m_index].first;
            m_pkt.seqnum = m_seq;
            m_pkt.acknum = m_seq;
            std::copy(std::cbegin(msg.data), std::cend(msg.data), std::begin(m_pkt.payload));
            m_pkt.checksum = pUtils->calculateCheckSum(m_pkt);
            assert(m_pkt.checksum == pUtils->calculateCheckSum(m_pkt));

            cache[m_index].second = false;
            pns->startTimer(SENDER, Configuration::TIME_OUT, m_seq);
            pns->sendToNetworkLayer(RECEIVER, m_pkt);
            rlog.verbose("Sender sent packet {}, with content {{}}.", m_seq, rlib::impl::payloadToString(msg.data));
            return true;
        }
    }
    virtual void receive(Packet &pkt) override {
        if(confirmedSeq < pkt.seqnum) {
            if(pkt.checksum != pUtils->calculateCheckSum(pkt)) return;

            auto m_index = pkt.seqnum % windowSize;
            if(cache[m_index].second)
                return; //! already confirmed.

            cache[m_index].second = true; //! confirmed!!
            pns->stopTimer(SENDER, pkt.seqnum);
            refreshWindow();
       }
    }
    virtual void timeoutHandler(int seq) override {
        rlog.verbose("Sender timed out at seq {}. Resending packet...", seq);
        pns->sendToNetworkLayer(RECEIVER, cache[seq%windowSize].first);
        pns->stopTimer(SENDER, seq); //! So many timer is of no use.
        pns->startTimer(SENDER, Configuration::TIME_OUT, seq);
    }
    virtual bool getWaitingState() override {
        if(confirmedSeq > 100 && confirmedSeq != maxSeqOnUse) return true; // do not send new packet
        return false; // OK to send next packet
    }
    virtual ~SRSender() override = default;

private:
    const pkt_seq_t windowSize;
    pkt_seq_t confirmedSeq = 0;

    std::queue<Message> queuedMessages;
    std::vector<std::pair<Packet, bool>> cache;
    //!              pair<pkt, confirmed>

    pkt_seq_t maxSeqOnUse = 0;
    //! cache_bottom_index is confirmedSeq+1 % windowSize

    void refreshWindow() {
        //! check confirmed packets in cache(window), push confirmedSeq to go, 
        //!   fetch necessary queuedMessage into cache(window) to send.

        for(auto seq = confirmedSeq + 1; seq <= maxSeqOnUse; ++seq) {
            auto m_index = seq % windowSize;
            if(cache[m_index].second == false) {
                //! first un-confirmed packet.
                break;
            }
            ++confirmedSeq;
            rlog.verbose("Sender finally confirmed packet {}, confirmedSeq updated to {}.", seq, confirmedSeq);
            rlog.debug("Current window [{}]", cache);

            //! fetch a queued message if possible
            if(!queuedMessages.empty()) {
                if(!send_impl(queuedMessages.front()))
                    //! The cache is full again!
                    throw std::logic_error("Programming error: cache must not be full, but send_impl failed."); 
                queuedMessages.pop();               
            }
        }
    }
};

#endif
