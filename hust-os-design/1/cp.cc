#include <rlib/sys/sio.hpp>
#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include <rlib/string.hpp>
#include <thread>
#include "util.hpp"

using namespace rlib;
using namespace rlib::literals;

void do_copy(string src, string dst, ProcGUI *guiPtr);

int main(int argc, char **argv) {
    opt_parser args(argc, argv);
    bool guiMode = args.getBoolArg("--gui");
    auto windowTitle = args.getValueArg("--title", false, args.getSelf());
    if(args.data().size() != 2)
        throw std::runtime_error("Copies two file stream.\nUsage: cp $srcFname $dstFname\nOptions: [--gui] [--title $title]");
    auto src = args.data()[0];
    auto dst = args.data()[1];

    // GUI business.
    auto app = Gtk::Application::create(); // Requires GTKmm 3.6+ to set empty application id. See Ref.
    ProcGUI procGUI(windowTitle, "Copied: 0B");
    if(guiMode) {
        std::thread(&do_copy, src, dst, &procGUI).detach();
        app->run(procGUI);
    }
    else {
        do_copy(src, dst, nullptr);
    }
}

void do_copy(string src, string dst, ProcGUI *guiPtr) {
    auto srcFd = open(src.c_str(), O_RDONLY);
    auto dstFd = creat(dst.c_str(), get_file_permission(src));
    if(srcFd == -1) throw std::runtime_error("Unable to open {} for read, {}"_rs.format(src, strerror(errno)));
    rlib_defer([&]{ close(srcFd); });
    if(dstFd == -1) throw std::runtime_error("Unable to open {} for write, {}"_rs.format(src, strerror(errno)));
    rlib_defer([&]{ close(dstFd); });

    constexpr size_t buf_size = 4096; // 64K
    char buf[buf_size];
    time_t last_update_time = time(NULL);
    while(true) {
        auto size = read(srcFd, buf, buf_size);
        if(size == -1) throw std::runtime_error("read error");
        if(size == 0) break; // EOF
        rlib::fdIO::writen_ex(dstFd, buf, size);
        if(guiPtr) {
            guiPtr->copiedBytes += size;
            if(auto curr_time = time(NULL); curr_time > last_update_time) {
                last_update_time = curr_time;
                guiPtr->dispatcher.emit(); // Only once per second.
            }
        }
    }

    if(guiPtr) {
        guiPtr->finished = true;
        guiPtr->dispatcher.emit();
    }
}



