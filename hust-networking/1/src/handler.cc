#include "handler.hpp"
#include <rlib/sys/sio.hpp>
#include <rlib/scope_guard.hpp>
#include "log.hpp"
#include "http.hpp"
#include "req_processor.hpp"

using namespace std::string_literals;

void handler::do_conn(sockfd_t connfd, const server_config &conf) {
    rlib_defer([&](){close(connfd);});
    http_request req;
    unsigned current_status = 200;
    std::string status_reason;
    auto peer_info = rlib::get_peer_name(connfd);
    std::string peer_addr = peer_info.first + ":" + std::to_string(peer_info.second);
    //! This block will receive and parse http request.
    try {
        std::string req_data;
        do {
            //! Incomplete message. recv again.
            req_data += rlib::sockIO::quick_recvall(connfd);
            break;
        } while(req_data.size() < 4 || req_data.substr(req_data.size()-4) != "\r\n\r\n");
        req = http_parser::parse_request(req_data);
    }
    catch(std::exception &e) {
        current_status = (e.what() == "505"s) ? 505 : 400;
        status_reason = std::string(e.what());
    }
    //! Ok. Do response. 
    auto resp = http_req_processor::process(req, conf, current_status, status_reason);
    rlog.info("{}: {} {}, {}, with {}.", peer_addr, req.op, req.uri, resp.status, req.headers["User-Agent"]);
    return rlib::sockIO::quick_send(connfd, http_parser::format_response(resp));
}
