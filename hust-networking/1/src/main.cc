#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include <rlib/log.hpp>

#include "config.hpp"
#include "server.hpp"

void show_help() {
    rlib::println(std::cout, R"RSTR(
HUST Network homework
    Copyright (C) 2018 Recolic Keghart <root@recolic.net>
    Licensed under Modified Mozilla Public License

Usage:
    ./this_homework -c <config_file> # Run it!
    ./this_homework --conf <config_file>
    ./this_homework --help # Show this message
)RSTR");
}

int main(int arglen, char **argv) {
    //rlog.set_log_level(rlib::log_level_t::DEBUG);
    rlib::opt_parser args(arglen, argv);
    if(args.getBoolArg("--help", "-h")) {
        show_help();
        exit(0);
    }
    auto confPath = args.getValueArg("--conf", "-c");
    server_config config = configuration_parser::parse(confPath);

    rhttp_server rhttp(config);
    rhttp.run_all();

    //! Main thread sleep forever.
    std::condition_variable cv;
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, []{return false;});
}
