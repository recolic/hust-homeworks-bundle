#ifndef HUST___GENERAL_UI_HPP_
#define HUST___GENERAL_UI_HPP_

#include <cpp-readline/src/Console.hpp>

#include <functional>
#include <string>
#include <iostream>
#include <list>

#include <unistd.h>
#include <csignal>
#include <cstdio>

#include <rlib/stdio.hpp>
#include <rlib/terminal.hpp>
#include <rlib/string/string.hpp>

#include <rlib/sys/os.hpp>

using namespace rlib::terminal;
using rlib::splitString;

class fake_terminal {
#ifdef FORCE_MULTICOLOR_RTERM
    static constexpr bool force_multicolor = true;
#else
    static constexpr bool force_multicolor = false;
#endif
    static void _clear() {rlib::printf("\033[H\033[J");}
    //static void _clear() {system("tput clear");}
    //static void _clear() {rlib::printf("\x5b\x1b\x4a\x33\x5b\x1b\x1b\x48\x32\x5b\x00\x4a");}
public:
    using callback_t = std::function<void (std::vector<std::string>)>;
    static void sigint_handler(int) {
        if(is_scripting())
            exit(127);
        rlib::println();
        if(force_multicolor || rlib::OSInfo::os != rlib::OSInfo::os_t::WINDOWS)
            rlib::printfln("Use {}exit{} to exit.", font_t::bold, clear);
        else
            rlib::println("Use `exit` to exit.");
        rlib::print(prompt());
        std::cout.flush();
    }

    [[noreturn]] static void go(const callback_t &callback) {
        //CppReadline::Console console(prompt());
#ifdef ENABLE_SILLY_FAKE_MENU
        if(!is_scripting()) _clear();
#endif
        if(!is_scripting()) rlib::println(welcome());
        signal(SIGINT, fake_terminal::sigint_handler);
        while(true) {
#ifdef ENABLE_SILLY_FAKE_MENU
            if(!is_scripting()) callback(std::vector<std::string>{"help"});
#endif
            if(!is_scripting()) rlib::print(prompt());
            try {
                auto cont = rlib::scanln();
#ifdef ENABLE_SILLY_FAKE_MENU
                if(!is_scripting()) _clear();
#endif
                size_t pos = cont.find('#');
                if(pos != std::string::npos)
                    cont = cont.substr(0, pos); //Remove comments. Avoid rlib::splitString to make it faster.
                callback(splitString(cont));
            }
            catch(std::exception &e) {
                showError(e.what());
                if(is_scripting()) {
                    rlib::println("Exiting because of previous error...");
                    std::exit(5);
                }
            }
            if(std::cin.eof())
                std::exit(0);
        }
    }
private:
    static bool is_scripting() __attribute__((pure, const)) {
#define WINDOWS 123
#if RLIB_OS_ID == WINDOWS
        return !_isatty(fileno(stdin));
#else
        return !isatty(fileno(stdin));
#endif
#undef WINDOWS
    }
    static string prompt() {
        if(force_multicolor || rlib::OSInfo::os != rlib::OSInfo::os_t::WINDOWS)
            return rlib::format_string("{}rfaketerm 0.3.1{} {}~{} ", color_t::green, clear, font_t::bold, clear);
        else
            return "rfaketerm 0.3.1 ~";
    }
    static string welcome() {
        if(force_multicolor || rlib::OSInfo::os != rlib::OSInfo::os_t::WINDOWS)
            return rlib::format_string("{}Welcome to rfaketerm 0.3.1. Use {}help{}{} to show usage.{}", color_t::blue, font_t::bold, clear, color_t::blue, clear);
        else
            return "Welcome to rfaketerm 0.3.1. Use `help` to show usage.";
    }
    static void showError(const std::string &msg) {
        if(force_multicolor || rlib::OSInfo::os != rlib::OSInfo::os_t::WINDOWS)
            rlib::printfln("{}{}Error{}{}: {}{}", color_t::red, font_t::bold, clear, color_t::lightgray, msg, clear);
        else
            rlib::printfln("Error: {}", msg);
    }
};

#endif
