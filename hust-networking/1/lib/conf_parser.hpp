#ifndef _NETW_CONF_PARSER_HPP
#define _NETW_CONF_PARSER_HPP 1

#include "dump_file.hpp"
#include <unordered_map>
#include <list>
#include <rlib/stdio.hpp>

namespace rlib::impl {
    using conf_kv_type = std::unordered_map<std::string, std::string>;
    using conf_content_type = std::unordered_multimap<std::string, conf_kv_type>;

    inline rlib::string get_kv_value(const conf_kv_type &kv, const std::string &k) {
        try {
            return kv.at(k);
        } catch(std::out_of_range &) {
            throw std::out_of_range("configuration file: required key {} not exist."_format(k));
        }
    }
    inline rlib::string get_kv_value(const conf_kv_type &kv, const std::string &k, const std::string &def) {
        try {
            return get_kv_value(kv, k);
        }
        catch(std::out_of_range &) {
            return def;
        }
    }

    inline conf_content_type parse_conf(const std::string &filename) {
        conf_content_type res;
        rlib::string content = dump_file(filename);
        std::unordered_map<std::string, std::string> *current_section;
        // \r is not supported, \r\n will be stripped.
        for (auto &&line : content.split('\n')) {
            line.strip();
            if (line[0] == '#')
                continue;
            else if (line[0] == '[') {
                auto pos = line.find(']');
                if (pos == std::string::npos)
                    continue;
                auto section_name = line.substr(1, pos - 1);
                auto iter = res.emplace(section_name, std::unordered_map<std::string, std::string>());
                current_section = &iter->second;
            } else {
                auto pos = line.find('=');
                rlib::string key_name = line.substr(0, pos), val_name = line.substr(pos + 1);
                key_name.strip(), val_name.strip();
                current_section->emplace(key_name, val_name);
            }
        }
        return res;
    }
}


#endif //_NETW_CONF_PARSER_HPP
