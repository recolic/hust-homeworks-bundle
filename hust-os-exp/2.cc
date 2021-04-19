#include <condition_variable>
#include <thread>
#include <mutex>

#include <rlib/stdio.hpp>

int a = 0;
std::mutex a_m;
std::condition_variable a_cv;
bool processed = false;

void adder_thread() {
    for(auto cter = 1; cter < 101; ++cter) {
        std::unique_lock<std::mutex> lk(a_m);
        a_cv.wait(lk, []{return processed;});
        a+= cter;
        processed = false;
        lk.unlock();
        a_cv.notify_one();
    }
}

void printer_thread() {
    while(true) {
        std::unique_lock<std::mutex> lk(a_m);
        a_cv.wait(lk, []{return !processed;});
        rlib::println("Current a is", a);
        processed = true;
        lk.unlock();
        a_cv.notify_one();
    }
}

int main() {
    std::thread(&printer_thread).detach();
    adder_thread();
}

