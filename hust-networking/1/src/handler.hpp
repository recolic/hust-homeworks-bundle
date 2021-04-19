#ifndef NETW_HANDLER_HPP
#define NETW_HANDLER_HPP

#include <rlib/class_decorator.hpp>
#include <string>
#include <rlib/pool.hpp>
#include <rlib/class_decorator.hpp>
#include <rlib/sys/fd.hpp>
#include "config.hpp"
#include "lib/thread_pool.hpp"

class handler : rlib::noncopyable {
    using this_type = handler;
public:
    handler(int worker_threads)
        : pool(worker_threads ? worker_threads : 64) {

    }
    void add_task(sockfd_t connfd, const server_config &conf) {
        pool.borrow_one()->issue(std::bind(&this_type::do_conn, this, connfd, conf));
    }

private:
    void do_conn(sockfd_t connfd, const server_config &conf);

    rlib::impl::fixed_thread_pool pool;
};

#endif
