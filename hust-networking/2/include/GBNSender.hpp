#ifndef _RNETW_GBN_SENDER_HPP_
#define _RNETW_GBN_SENDER_HPP_

#include "RdtSender.h"
#include "Global.h"
#include "../lib/rlog.hpp"
#include <cstdint>
#include <cassert>
#include <vector>
#include <queue>

class GBNSender final : public RdtSender {
    using pkt_seq_t = decltype(Packet::seqnum);
public:
    GBNSender(const pkt_seq_t windowSize) : windowSize(windowSize), cache(windowSize) {
        //! You are smart enough to know what I'm doing here.
        assert(windowSize * 2 > windowSize);
    }
    virtual bool send(Message &msg) override {
        if(!send_impl(msg))
            queuedMessages.push(msg);
        return true;
    }
    bool send_impl(Message &msg) {
        rlog.debug("-- send impl: current confirmed seq {}", confirmedSeq);
        if(confirmedSeq + windowSize <= maxSeqOnUse) {
            //! The cache is full! Message must be queued and wait.
            rlog.verbose("window full. pushing message to queue.");
            return false;
        }
        else {
            //! The window is not full. Send the message.
            ++maxSeqOnUse;
            auto m_seq = maxSeqOnUse;
            auto m_index = m_seq % windowSize;

            Packet &m_pkt = cache[m_index];
            m_pkt.seqnum = m_seq;
            m_pkt.acknum = m_seq;
            std::copy(std::cbegin(msg.data), std::cend(msg.data), std::begin(m_pkt.payload));
            m_pkt.checksum = pUtils->calculateCheckSum(m_pkt);
            assert(m_pkt.checksum == pUtils->calculateCheckSum(m_pkt));

            pns->startTimer(SENDER, Configuration::TIME_OUT, m_seq);
            pns->sendToNetworkLayer(RECEIVER, m_pkt);
            rlog.verbose("Sender sent packet {}, with content {{}}.", m_seq, rlib::impl::payloadToString(msg.data));
            return true;
        }
    }
    virtual void receive(Packet &pkt) override {
        if(confirmedSeq < pkt.acknum) {
            if(pkt.checksum != pUtils->calculateCheckSum(pkt)) return;

            for(auto seq = confirmedSeq + 1; seq <= pkt.acknum; ++seq) {
                pns->stopTimer(SENDER, seq);
            }
            confirmedSeq = pkt.acknum;
            rlog.verbose("Sender received confirmation {}, confirmedSeq updated.", pkt.acknum);
            rlog.debug("Current window [{}]", cache);

            //! check queuedMessages and send them!
            while(!queuedMessages.empty()) {
                if(!send_impl(queuedMessages.front()))
                    break; //! The cache is full again!
                queuedMessages.pop();
            }
            //! no more msg available to send.
        }
    }
    virtual void timeoutHandler(int seq) override {
        rlog.verbose("Sender timed out at seq {}. Resending packet from {} to {}...", seq, confirmedSeq+1, maxSeqOnUse);
        for(auto seq = confirmedSeq + 1; seq <= maxSeqOnUse; ++seq) {
            assert(cache[seq%windowSize].seqnum == seq);
            pns->sendToNetworkLayer(RECEIVER, cache[seq%windowSize]);
            pns->stopTimer(SENDER, seq); //! So many timer is of no use.
        }
        pns->startTimer(SENDER, Configuration::TIME_OUT, maxSeqOnUse);
    }
    virtual bool getWaitingState() override {
        if(confirmedSeq > 100 && confirmedSeq != maxSeqOnUse) return true; // do not send new packet
        return false; // OK to send next packet
    }
    virtual ~GBNSender() override = default;

private:
    const pkt_seq_t windowSize;
    pkt_seq_t confirmedSeq = 0;
    std::queue<Message> queuedMessages;
    std::vector<Packet> cache;
    pkt_seq_t maxSeqOnUse = 0;
    //! cache_bottom_index is confirmedSeq+1 % windowSize
};

#endif
