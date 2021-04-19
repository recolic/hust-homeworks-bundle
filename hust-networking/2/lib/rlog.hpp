#ifndef _NETSIM_RLOG_HPP_
#define _NETSIM_RLOG_HPP_ 1

#include <rlib/require/cxx17>
#include <rlib/log.hpp>
inline rlib::logger rlog(std::cerr);

using uint32_t = unsigned int;
using rlib::literals::operator""_format;

#include <rlib/3rdparty/prettyprint.hpp>
using namespace rlib::_3rdparty::std;

#include <iostream>
#include "../include/Global.h"
using namespace std::literals;
namespace rlib::impl {
    template <typename CharArrT>
    std::string payloadToString(const CharArrT &arr) {
        std::string str;
        std::copy(std::begin(arr), std::end(arr), std::back_inserter(str));
        return str;
    }
}
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<< (std::basic_ostream<CharT, Traits> &os, const Packet& p) {
	auto real_str = "{Packet: seq "s + std::to_string(p.seqnum) + ", ack "+std::to_string(p.acknum)+", checksum "+(p.checksum == pUtils->calculateCheckSum(p) ? "valid" : "incorrect")+", payload `"+rlib::impl::payloadToString(p.payload)+"`}";
    os << real_str;
    return os;
}
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<< (std::basic_ostream<CharT, Traits> &os, const std::pair<Packet, bool>& p) {
	os << p.first << (p.second ? "(confirmed)" : "(fresh)");
    return os;
}




#endif
