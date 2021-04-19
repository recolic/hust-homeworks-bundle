//
// Created by recolic on 18-10-31.
//

#ifndef NETW_LISTENER_HPP
#define NETW_LISTENER_HPP

#include <rlib/sys/fd.hpp>
#include <string>
#include <list>
#include "config.hpp"
#include "handler.hpp"
#include <rlib/sys/sio.hpp>
#include "log.hpp"

class listener : rlib::noncopyable {
public:
    listener(const std::string &bind_addr, uint16_t bind_port, 
        const general_config &general, std::list<vhost_config> my_vhosts, handler &my_handler)
        : bind_addr(bind_addr), bind_port(bind_port), 
          my_conf{general, std::move(my_vhosts)}, my_handler(my_handler) 
    {}
    [[noreturn]] void run() {
        rlog.info("Listening {}:{} for incoming connections...", bind_addr, bind_port);
        auto listenfd = rlib::quick_listen(bind_addr, bind_port);
        while(true) {
            try {
                auto connfd = rlib::quick_accept(listenfd);
                my_handler.add_task(connfd, my_conf);
            }
            catch (std::exception &e) {
                rlog.fatal("Listener thread exception caught: {}", e.what());
            }
        }
    }


private:
    std::string bind_addr;
    uint16_t bind_port;
    server_config my_conf;
    handler &my_handler;
};


#endif //NETW_LISTENER_HPP
