#include "lib/thread_pool.hpp"
#include <rlib/stdio.hpp>
#include <thread>
using namespace rlib;
using namespace std::literals;

int main() {
    auto task = []() {
        println("Thread", std::this_thread::get_id(), "sleeping...");
        std::this_thread::sleep_for(3s);
        println("Thread", std::this_thread::get_id(), "waked up...");
    };

    rlib::impl::fixed_thread_pool pool(4);
    for(auto cter = 0; cter < 10; ++cter) {
        println("Launching task", cter);
        auto *ptr = pool.borrow_one();
        ptr->issue(task);
        println("Launched task", cter);
    }
    println("Joining...");
    pool.join_all();
    println("Joined!");
}
