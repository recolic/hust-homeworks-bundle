#include <rlib/stdio.hpp>
#include <thread>
#include <chrono>
#include <cassert>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


#include <rlib/sys/sio.hpp>
using rlib::println;
using namespace rlib::literals;
using namespace std::chrono_literals;

template <typename FuncType, typename TimeType>
void timed_callback(FuncType func, TimeType time) {
    std::thread([&]{
                std::this_thread::sleep_for(time);
                func();
            }).detach();
}

std::function<void()> *real_handler = nullptr;
void handler(int) {
    (*real_handler)();
    exit(0);
}

int main() {
    fd_t fPipe[2];
    assert(0 == pipe(fPipe));
    assert(SIG_ERR != signal(SIGINT, &handler));

    auto pids = std::make_pair(fork(), fork());
    auto times = 0;
    if(pids.first + pids.second == 0) exit(0);
    if(pids.first == 0) {
        // child 1
        auto h = [] {
            println("subprocess 1 is killed by par");
        };
        real_handler = new std::function<void()>(h);
        close(fPipe[0]);
        while(true) {
            const auto str = "I send you {} times"_format(++times);
            rlib::fdIO::quick_write(fPipe[1], str);
            std::this_thread::sleep_for(1s);
        }
    }
    else if(pids.second == 0) {
        // child 2
        auto h = [] {
            println("subprocess 2 is killed by par");
        };
        real_handler = new std::function<void()>(h);
        close(fPipe[1]);
        while(true) {
            try {
                println(rlib::fdIO::quick_readall(fPipe[0]));
            } catch(...) {}
        }
    }
    else {
        // parent
        // no error check
        println("childs: ", pids.first, pids.second);
        auto h = [=] {
            kill(pids.first, SIGINT);
            waitpid(pids.first, NULL, NULL);
            kill(pids.second, SIGINT);
            waitpid(pids.second, NULL, NULL);
            println("parent proc is killed now");
        };
        real_handler = new std::function<void()>(h);
        timed_callback([]{
                    kill(getpid(), SIGINT);
                }, 15s);
        while(true);
   }
}
