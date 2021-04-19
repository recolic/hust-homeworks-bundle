#ifndef R_HTTP_HPP
#define R_HTTP_HPP

#include <string>
#include <unordered_map>
#include <rlib/string.hpp>
using namespace rlib::literals;

struct http_request {
    std::string op; //! GET / POST
    std::string version; //! HTTP/1.0, HTTP/1.1, HTTP/2.0
    std::string uri;

    std::unordered_map<std::string, std::string> headers;

    //! Payload is not supported, because POST is not supported.
};

struct http_response {
    std::string version; //! HTTP/1.0, HTTP/1.1, HTTP/2
    unsigned status;

    std::unordered_map<std::string, std::string> headers; //! You need not appoint `Content-Length` header. It will be overwritten.

    std::string payload;
};

class http_parser : rlib::static_class {
    static constexpr const char *SP = " ";
    static constexpr const char *CRLF = "\r\n";
public:
    static http_request parse_request(const rlib::string &data) {
        http_request req;
        auto lines = data.split(CRLF);
        auto line1 = lines[0].split(SP);
        if(line1.size() != 3) 
            throw std::invalid_argument("invalid version line");
        if(line1[0] == "GET" || line1[0] == "POST")
            req.op = line1[0];
        else
            throw std::invalid_argument("unsupported http op type");
        req.uri = line1[1];
        if(line1[2] == "HTTP/1.0" || line1[2] == "HTTP/1.1")
            req.version = line1[2];
        else if(line1[2] == "HTTP/2")
            throw std::invalid_argument("505");
        else
            throw std::invalid_argument("invalid http version");
        lines.erase(lines.begin());
        for(auto &&header_line : lines) {
            if(header_line.empty()) continue;
            auto header_kv = header_line.split(": ");
            if(header_kv.size() != 2)
                throw std::invalid_argument("invalid header kv");
            req.headers.insert({header_kv[0], header_kv[1]});
        }
        return req;
    }
    static std::string format_response(const http_response &resp) {
        std::string result = resp.version + SP + std::to_string(resp.status) + SP + http_status_to_reason(resp.status) + CRLF;
        for(auto &&header : resp.headers) {
            std::string header_line = header.first + ": " + header.second + CRLF;
            result += header_line;
        }
        result += CRLF;
        result += resp.payload;
        return result;
    }
private:
    static constexpr const char *http_status_to_reason(unsigned status) {
        switch(status) {
            case 100: return "Continue";
            case 101: return "Switching Protocols";
            case 200: return "OK";
            case 201: return "Created";
            case 202: return "Accepted";
            case 203: return "Non-Authoritative Information";
            case 204: return "No Content";
            case 205: return "Reset Content";
            case 206: return "Partial Content";
            case 300: return "Multiple Choices";
            case 301: return "Moved Permanently";
            case 302: return "Found";
            case 303: return "See Other";
            case 304: return "Not Modified";
            case 305: return "Use Proxy";
            case 307: return "Temporary Redirect";
            case 400: return "Bad Request";
            case 401: return "Unauthorized";
            case 402: return "Payment Required";
            case 403: return "Forbidden";
            case 404: return "Not Found";
            case 405: return "Method Not Allowed";
            case 406: return "Not Acceptable";
            case 407: return "Proxy Authentication Required";
            case 408: return "Request Time-out";
            case 409: return "Conflict";
            case 410: return "Gone";
            case 411: return "Length Required";
            case 412: return "Precondition Failed";
            case 413: return "Request Entity Too Large";
            case 414: return "Request-URI Too Large";
            case 415: return "Unsupported Media Type";
            case 416: return "Requested range not satisfiable";
            case 417: return "Expectation Failed";
            case 500: return "Internal Server Error";
            case 501: return "Not Implemented";
            case 502: return "Bad Gateway";
            case 503: return "Service Unavailable";
            case 504: return "Gateway Time-out";
            case 505: return "HTTP Version not supported";
            default: throw std::invalid_argument("unknown http status code {}, unable to parse"_format(status));
        }
    }
};

#endif


