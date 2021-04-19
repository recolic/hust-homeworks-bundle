#ifndef RLIB_NAIVE_MUTEX_HPP_
#define RLIB_NAIVE_MUTEX_HPP_ 1

#include <atomic>
#include <stdexcept>

namespace rlib {

//! Mutex with standard layout.
class stdlayout_mutex {
public:
    stdlayout_mutex() : locked(false) {}
    void lock() {
        while(true) {
            if(try_lock()) return;
        }
    }
    bool try_lock() {
        bool expected = false;
        return locked.compare_exchange_strong(expected, true);
    }
    bool is_locked() {
        return locked;
    }
    void unlock() {
        if(not locked)
            throw std::logic_error("unlock a unlocked mutex.");
        bool expected = true;
        while(not locked.compare_exchange_strong(expected, false))
            ; // Try again
    }
private:
    std::atomic<bool> locked;

};

}


#endif
