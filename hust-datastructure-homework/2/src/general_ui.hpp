#ifndef HUST___GENERAL_UI_HPP_
#define HUST___GENERAL_UI_HPP_

#include <functional>
#include <string>
#include <iostream>
#include <list>

#include <rlib/stdio.hpp>
#include <rlib/terminal.hpp>
#include <rlib/string/string.hpp>

#include <rlib/sys/os.hpp>

using namespace rlib::terminal;
using rlib::splitString;

class fake_terminal {
public:
    using callback_t = std::function<void (std::list<std::string>)>;
    [[noreturn]] static void go(const callback_t &callback) {
        while(true) {
            prompt();
            callback(splitString(rlib::io::scanln()));
        }
    }
private:
    static void prompt() {
        if constexpr(rlib::OSInfo::os == rlib::OSInfo::os_t::WINDOWS) {
            rlib::io::print(color_t::green, "rfaketerm 0.0", clear, font_t::bold, "~", clear);
        }
        else {
            rlib::io::print(color_t::green, "rfaketerm 0.0", clear, font_t::bold, "~", clear);
        }
    }
};

#endif
