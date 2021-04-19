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
    using callback_t = std::function<void (std::vector<std::string>)>;
    static void showError(const std::string &msg) {
        rlib::printfln("{}{}Error{}{}: {}{}", color_t::red, font_t::bold, clear, color_t::lightgray, msg, clear);
    }

    [[noreturn]] static void go(const callback_t &callback) {
        callback(splitString("help"));
        while(true) {
            prompt();
            try {
                callback(splitString(rlib::scanln()));
            }
            catch(std::exception &e) {
                showError(e.what());
            }
            if(std::cin.eof())
                std::exit(0);
        }
    }
private:
    static void prompt() {
        if constexpr(rlib::OSInfo::os == rlib::OSInfo::os_t::WINDOWS) {
            rlib::printf("rfaketerm 0.2 ~");
        }
        else {
            rlib::printf("{}rfaketerm 0.2{} {}~{} ", color_t::green, clear, font_t::bold, clear);
        }
    }
};

#endif
