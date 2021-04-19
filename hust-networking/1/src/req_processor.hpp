#ifndef NETW_REQ_PROC_HPP
#define NETW_REQ_PROC_HPP

#include "http.hpp"
#include "config.hpp"
#include <rlib/sys/os.hpp>
#include "messages.hpp"
#include "log.hpp"
#include "lib/dump_file.hpp"
#include <rlib/scope_guard.hpp>

#ifdef USE_MINGW_FS_FIX
#include "lib/mingw-filesystem-fix.hpp"
#else
#include <rlib/require/cxx17> //! For filesystem TS.
#include <filesystem>
#endif

class http_req_processor {
    static std::string fileNameToExtName(std::string filename) {
        auto pos = filename.rfind('/');
        if(pos != std::string::npos) {
            filename = filename.substr(pos+1);
        }
        pos = filename.rfind('.');
        if(pos != std::string::npos)
            return filename.substr(pos+1);
        else
            return "";
    }

    static char hex2char(char hexChar) {
        char val = hexChar - '0';
        if(val > 9)
            val -= 'A' - '9' - 1;
        return val;
    }
    static char hex2char(char hexChar1, char hexChar2) {
        //! Convert hex to char, E.x. "3F" to '?'
        return (hex2char(hexChar1) << 4) + hex2char(hexChar2);
    }

    struct decoded_uri_t {
        rlib::string path, get_param, subsection;
    };
    static decoded_uri_t uri_decode(const std::string &uri) {
        decoded_uri_t res;
        rlib::string *current_part = &res.path;
        for(auto cter = 0; cter < uri.size(); ++cter) {
            auto c = uri[cter];
            if(c == '?')
                current_part = &res.get_param;
            else if(c == '#')
                current_part = &res.subsection;
            else if(c == '%') {
                *current_part += hex2char(uri.at(cter+1), uri.at(cter+2));
                cter += 2;
            } else {
                *current_part += c;
            }
        }
        return res;
    }
    static std::string uri_encode(decoded_uri_t uri) {
        std::string result;
        result = uri.path.replace("%", "%25").replace("#", "%23").replace("&", "%26").replace("?", "%3F");
        if(!uri.get_param.empty()) {
            result += '?';
            result += uri.get_param.replace("%", "%25").replace("#", "%23");
        }
        if(!uri.subsection.empty()) {
            result += '#';
            result += uri.subsection.replace("%", "%25").replace("#", "%23");
        }
        return result;
    }

public:
    //! Note that the server_config here only contains available vhosts, rather than all vhosts.
    static http_response process(const http_request &req, const server_config &conf, unsigned error_code, const std::string &error_reason) noexcept {
        http_response resp;
        resp.status = error_code;
        rlib_defer([&](){resp.headers["Content-Length"] = resp.payload.size();});
        resp.version = req.version.empty() ? "HTTP/1.1" : req.version;
        if(error_code >= 400) {
            //! Error 40x and 50x here.
            resp.headers.insert({"Content-Type", "text/html"});
            rlib::string error_page_str;
            if(error_code == 400) error_page_str = msg::page_400;
            else if(error_code == 403) error_page_str = msg::page_403;
            else if(error_code == 404) error_page_str = msg::page_404;
            else if(error_code == 505) error_page_str = msg::page_505;
            else if(error_code/100 == 5) error_page_str = msg::page_50x;
            else error_page_str = "{}";
            resp.payload = error_page_str.format(error_reason);
        }
        else if(error_code == 200) {
            //! No error until now. Just parse the uri and give response.
#ifndef USE_MINGW_FS_FIX
            namespace fs = std::filesystem;
#endif
            //! Decode the uri
            decoded_uri_t decoded_uri;
            try {
                decoded_uri = uri_decode(req.uri);
            } catch(std::exception &e) {
                return process(req, conf, 400, "Failed to parse uri");
            }

            //! Get the vhost
            const vhost_config *p_vhost = nullptr;
            rlog.debug("vhost size {}", conf.vhosts.size());
            if(conf.vhosts.empty())
                return process(req, conf, 500, "No available vhost");
            try {
                auto requested_host = rlib::string(req.headers.at("Host")).split(':')[0].strip();
                for(const auto &vhost : conf.vhosts) {
                    rlog.debug("1 trying vhost {}", vhost.server_name);
                    if(vhost.server_name == requested_host) {
                        rlog.debug("1 using vhost {}", vhost.server_name);
                        p_vhost = &vhost;
                        break;
                    }
                }
            } catch(...) {}
            if(p_vhost == nullptr) {
                //! Use the default vhost...
                for(const auto &vhost : conf.vhosts) {
                    if(vhost.server_name == "default" || vhost.server_name == "*" || vhost.server_name == "") {
                        p_vhost = &vhost;
                        break;
                    }
                }
            }
            if(p_vhost == nullptr) {
                //! Fuck that there's still no vhost. Just use the first one.
                p_vhost = &*conf.vhosts.begin();
            }
            const vhost_config &vhost = *p_vhost;

            //! Get the full path
            std::string full_path;
            if(decoded_uri.path[decoded_uri.path.size() - 1] == '/') {
                bool file_found = false;
                for(const auto &index_file : vhost.index) {
                    full_path = vhost.root + decoded_uri.path + index_file;
#ifdef USE_MINGW_FS_FIX
                    if(mingw_file_exist(full_path)) {
#else
                    if(fs::is_regular_file(full_path) || fs::is_symlink(full_path)) {
#endif
                        file_found = true;
                        break; //! OK
                    }
                }
                if(!file_found)
                    return process(req, conf, 404, "File not found or is not regular file/sym link/dir");
            }
            else {
                full_path = vhost.root + decoded_uri.path;
#ifdef USE_MINGW_FS_FIX
                if(mingw_isdir(full_path)) {
#else
                if(fs::is_directory(full_path)) {
#endif
                    decoded_uri.path += '/';
                    return process(req, conf, 301, uri_encode(decoded_uri));
                }
#ifdef USE_MINGW_FS_FIX
                else if(mingw_file_exist(full_path)) {
#else
                else if(fs::is_regular_file(full_path) || fs::is_symlink(full_path)) {
#endif
                    //! OK
                }
                else {
                    return process(req, conf, 404, "File not found or is not regular file/sym link/dir");
                }
            }
            //! Read the file
            try {
                resp.payload = dump_file(full_path);
            } catch(std::exception &e) {
                return process(req, conf, 403, e.what());
            }
            //! Now the status code is surely 200!!!
            //! Set the mime if and only if other affairs are OK.
            try {
                auto extName = fileNameToExtName(full_path);
                resp.headers.insert({"Content-Type", conf.general.mime.at(extName)});
            } catch(...) {
                resp.headers.insert({"Content-Type", conf.general.default_type});
            }
        }
        else if(error_code >= 300) {
            //! Must do redirecting. Target uri is in error_reason.
            resp.headers.insert({"Content-Type", "text/html"});
            resp.headers.insert({"Location", error_reason});
            resp.payload = msg::page_30x;
        }
        else {
            //! Many errors are not supported.
            return process(req, conf, 500, "Unknown error");
        }

        return resp;
    }
};

#endif
