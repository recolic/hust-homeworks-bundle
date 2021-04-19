#ifndef NETW_SERVER_HPP
#define NETW_SERVER_HPP

#include "listener.hpp"
#include "handler.hpp"
#include "log.hpp"

class rhttp_server {
    using port_and_addr_t = std::pair<uint16_t, std::string>;
public:
    rhttp_server(const server_config &config) : mHandler(config.general.worker_threads) {
        //! First, redirect the access_log
        if(!config.general.access_log.empty()) {
            rlog.info("Logging into {}", config.general.access_log);
            rlog = rlib::logger(config.general.access_log);
        }

        std::list<std::list<vhost_config>> listener_sharing_list;
        for(const vhost_config &vhost : config.vhosts) {
            port_and_addr_t my_addr(vhost.listen_port, vhost.listen_addr);
            bool found_vhost = false;
            //! Check if I must share listener with an existing vhost.
            for(auto &l :  listener_sharing_list) {
                for(const auto &existing_vhost : l) {
                    if(existing_vhost.listen_port == vhost.listen_port) {
                        if(addr_fit(existing_vhost.listen_addr, vhost.listen_addr)) {
                            found_vhost = true;
                            l.push_back(vhost);
                            break;
                        }
                    }
                }
                if(found_vhost) break;
            }
            //! If I must not share listener, create a new one.
            if(!found_vhost) {
                std::list<vhost_config> l;
                l.push_back(vhost);
                listener_sharing_list.emplace_back(std::move(l));
            }
        }
        rlog.info("Launching {} vhosts in {} listeners.", config.vhosts.size(), listener_sharing_list.size());
        //! Now every vhost has found its listener! Launch these o.
        for(auto &&l : listener_sharing_list) {
            listeners.emplace_back(merge_bind_addr(l), l.begin()->listen_port, config.general, l, mHandler);
        }
    }
    void run_all() {
        for(auto &l : listeners) {
            std::thread(std::bind(&listener::run, &l)).detach();
        }
    }

private:
    std::list<listener> listeners;
    handler mHandler;

    static bool addr_fit(std::string l, std::string r) {
        if(l == "::" || l == "::0" || r == "::" || r == "::0" || l == r)
            return true;
        if(l == "0.0.0.0" && (r.find(':') == std::string::npos))
            return true;
        if(r == "0.0.0.0" && (l.find(':') == std::string::npos))
            return true;
        return false;
    }
    static std::string merge_bind_addr(const std::list<vhost_config> &l) {
        for(const auto &v : l) {
            // ipv6 dual stack addr first!
            if(v.listen_addr == "::0" || v.listen_addr == "::")
                return v.listen_addr;
        }
        for(const auto &v : l) {
            if(v.listen_addr == "0.0.0.0")
                return v.listen_addr;
        }
        return l.begin()->listen_addr;
    }
};

#endif
