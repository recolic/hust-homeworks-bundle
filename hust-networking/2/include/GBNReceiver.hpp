#ifndef _RNETW_GBN_RECV_HPP_
#define _RNETW_GBN_RECV_HPP_ 1

#include "Global.h"
#include "RdtReceiver.h"
#include "../lib/rlog.hpp"

#include <cstdint>
#include <vector>
#include <cassert>

class GBNReceiver final : public RdtReceiver {
    using pkt_seq_t = decltype(Packet::seqnum);
public:
    GBNReceiver(const pkt_seq_t windowSize) : windowSize(windowSize), cache(windowSize) {
        //! You are smart enough to know what I'm doing here.
        assert(windowSize * 2 > windowSize);
    }
    virtual void receive(Packet &pkt) override {
        rlog.verbose("RECV: raw: recv packet seq {}, confirmedSeq={}, windowSize={}.", pkt.seqnum, confirmedSeq, windowSize);
        if(pkt.seqnum <= confirmedSeq) {
            //! history packet
            do_send_ack();
            return;
        }
        if(pkt.seqnum > confirmedSeq + windowSize)
            //! future packet
            return;
        if(pkt.checksum != pUtils->calculateCheckSum(pkt))
            //! broken packet
            return;
        auto m_index = pkt.seqnum % windowSize;
        if(pkt.seqnum != confirmedSeq + 1) {
            //! future packet. cache and drop it.
            if(cache[m_index].seqnum != pkt.seqnum)
                cache[m_index] = std::move(pkt);
            return;
        }
        //! OKay! It's time to deliver to app layer.
        //! send ack only if pkt delivered to app layer.
        do_deliver(pkt);
        while(true) {
            auto nextSeq = confirmedSeq + 1, index = nextSeq % windowSize;
            if(cache[index].seqnum == nextSeq)
                do_deliver(cache[index]);
            else
                break;
        }
    }

    virtual ~GBNReceiver() override = default;

private:
    const pkt_seq_t windowSize;
    pkt_seq_t confirmedSeq = 0;
    std::vector<Packet> cache;

    void do_send_ack() const {
        Packet ackPkt;
        ackPkt.acknum = ackPkt.seqnum = confirmedSeq;
        std::fill(std::begin(ackPkt.payload), std::end(ackPkt.payload), NULL);
        ackPkt.checksum = pUtils->calculateCheckSum(ackPkt);
        pns->sendToNetworkLayer(SENDER, ackPkt);
    }
    void do_deliver(Packet &pkt) {
        Message msg;
        std::copy(std::cbegin(pkt.payload), std::cend(pkt.payload), std::begin(msg.data));
        pns->delivertoAppLayer(RECEIVER, msg);

        //! ack
        ++confirmedSeq;
        assert(pkt.seqnum == confirmedSeq); //! If it fails, here's a programming error.
        do_send_ack();
        rlog.verbose("Receiver: deliver packet {} to app layer and sent ack back.", confirmedSeq);
    }
};

#endif
