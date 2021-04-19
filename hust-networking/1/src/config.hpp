//
// Created by recolic on 18-10-31.
//

#ifndef NETW_CONFIG_HPP
#define NETW_CONFIG_HPP

#include <rlib/string.hpp>
#include <rlib/stdio.hpp>

#include <list>
#include "lib/dump_file.hpp"
#include "lib/conf_parser.hpp"

struct vhost_config {
    std::string listen_addr;
    uint16_t listen_port;
    std::string server_name;
    std::string root; //! server root path
    std::vector<rlib::string> index; //! usually index.html
    std::string error_page; //! Error page path. Not supported
    std::string proxy_pass; //! Not supported
};

struct general_config {
    std::unordered_map<std::string, std::string> mime; //! Map: ExtName -> MimeStr
    std::string default_type; //! text/plain is not set
    std::string access_log; //! logging path
    size_t worker_threads; //! Set to 0 to disable thread_pool and use one-thread-per-request.
};

struct server_config {
    general_config general;
    std::list<vhost_config> vhosts;
};

class configuration_parser : rlib::static_class {
public:
    /*! Parse nginx-like configuration file.
     *
     * \param fileName configuration file to parse
     * \return parsed server config.
     */
    static server_config parse(const std::string &fileName) {
        server_config result;
        auto parsed_conf = rlib::impl::parse_conf(fileName);
        bool general_parsed = false;
        for(const auto &section : parsed_conf) {
            if(section.first == "general") {
                result.general = parse_general(section.second);
                general_parsed = true;
            }
            else if(section.first == "vhost") {
                result.vhosts.push_back(parse_vhost(section.second));
            }
            else
                throw std::runtime_error("Invalid section in configuration file. Only `general` and `vhost` are allowed.");
        }
        if(!general_parsed)
            throw std::runtime_error("Configuration file is missing `general` section.");
        if(result.vhosts.empty())
            throw std::runtime_error("Configuration file is missing `vhost` section.");
        return result;
    }

private:

    /*! Parse general_config from conf file.
     *
     * \return general_config
     * \throws exception if the config file is bad (general.mime not found but required).
     */
    static general_config parse_general(const rlib::impl::conf_kv_type &kv) {
        general_config conf;
        auto mime_file_path = rlib::impl::get_kv_value(kv, "mime");
        conf.mime = parse_mime(mime_file_path);
        conf.default_type = rlib::impl::get_kv_value(kv, "default_type", "text/html");
        conf.access_log = rlib::impl::get_kv_value(kv, "access_log", "");
        conf.worker_threads = rlib::impl::get_kv_value(kv, "worker_threads", "0").as<size_t>();
        return conf;
    }

    /*! Parse vhost_config from conf file.
     *
     * \return vhost_config
     * \throws exception if the config file is bad (something not found but required).
     */
    static vhost_config parse_vhost(const rlib::impl::conf_kv_type &kv) {
        vhost_config conf;
        // TODO: Parse statement `Listen`
        conf.listen_addr = rlib::impl::get_kv_value(kv, "listen_addr", "::");
        conf.listen_port = rlib::impl::get_kv_value(kv, "listen_port").as<uint16_t>();
        conf.server_name = rlib::impl::get_kv_value(kv, "server_name", "default");
        conf.error_page = rlib::impl::get_kv_value(kv, "error_page", "");
        conf.index = rlib::impl::get_kv_value(kv, "index").split();
        conf.root = rlib::impl::get_kv_value(kv, "root");
        return conf;
    }

    /*! Parse mime.types file.
     *
     * \return mime map.
     */
     static std::unordered_map<std::string, std::string> parse_mime(const std::string &path) {
        rlib::string content = dump_file(path);
        std::unordered_map<std::string, std::string> result;
        for(auto &&line : content.split('\n')) {
            auto linearr = line.strip().split();
            auto mime = linearr[0];
            linearr.erase(linearr.begin());
            for(auto &&ele : linearr) {
                if(!ele.empty())
                    result[ele.strip()] = mime.strip();
            }
        }
        return result;
     }
};


#endif //NETW_CONFIG_HPP
