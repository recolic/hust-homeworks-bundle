#include <utility>
#include <stdlib.h>
#include <unistd.h>
#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include <rlib/sys/unix_handy.hpp>

#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    // INPUT --> PIPE1 --> PIPE2 --> OUTPUT
    //      ProcA     ProcB     ProcC
    rlib::opt_parser args(argc, argv);
    if(args.data().size() != 2)
        throw std::runtime_error("Copies two file stream.\nUsage: game $srcFname $dstFname");
    auto src = args.data()[0];
    auto dst = args.data()[1];

    auto pipe1 = "/tmp/recolic-hust-os-fifo-518922714", pipe2 = "/tmp/recolic-hust-os-fifo-125350723";
    remove(pipe1); remove(pipe2); // Just make a try. No error check.
    if(mkfifo(pipe1, 0666) == -1 || mkfifo(pipe2, 0666) == -1)
        throw std::runtime_error("mkfifo");

    auto pids = std::make_pair(fork(), fork());
    if(pids.first == -1 || pids.second == -1)
        throw std::runtime_error("fork");
    rlib::println(pids.first, pids.second);

    if(pids.first == 0 && pids.second == 0)
        exit(0); // Too many processes...
    if(pids.first == 0) {
        // Proc A
        rlib::execs("./cp", std::vector<std::string>{src, pipe1, "--gui", "--title", "A"});
    }
    else if(pids.second == 0) {
        // Proc B
        rlib::execs("./cp", std::vector<std::string>{pipe1, pipe2, "--gui", "--title", "B"});
    }
    else {
        // Proc C
        rlib::execs("./cp", std::vector<std::string>{pipe2, dst, "--gui", "--title", "C"});
    }
    throw std::runtime_error("execl returns.");
}

