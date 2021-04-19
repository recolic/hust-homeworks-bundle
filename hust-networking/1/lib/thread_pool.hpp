#ifndef NETW_THREAD_POOL_HPP
#define NETW_THREAD_POOL_HPP

#include <rlib/pool.hpp>
#include <rlib/stdio.hpp>
#include "src/log.hpp"

namespace rlib {

namespace impl {
class fixed_thread_pool;
class containered_thread {
public:
    using this_type = containered_thread;
    using pool_type = fixed_thread_pool;
    /*! Constructor for containered thread.
     *
     */
    containered_thread(pool_type *pool_ptr) : pool_ptr(pool_ptr),
        real_thread(std::bind(&this_type::real_thread_proc, this)), must_join(false) {
    }
    /*! Issue a task by the contained thread.
     *  `pool.release_one` will be called after the task.
     *
     * \param task to issue
     */
    void issue(std::function<void()> task) {
        new_task_assigned = true;
        task_to_issue = std::move(task);
        sig_task_assigned.notify_one();
    }
    void join() {
        must_join = true;
        sig_task_assigned.notify_one();
        real_thread.join();
    }
private:
    [[noreturn]] void real_thread_proc() {
        while(true) {
            {
                try {
                    std::unique_lock<std::mutex> lk(m);
                    sig_task_assigned.wait(lk, [this]{return new_task_assigned || must_join;});
                } catch (std::system_error &e) {
                    rlog.error("System Error on std::unique_lock.lock, {}:{}, errno is {}", e.code(), e.what(), strerror(errno));
                    continue;
                }
            }
            if(must_join) break;
            task_to_issue();
            reinterpret_cast<fixed_object_pool<this_type, fixed_thread_pool *> *>(pool_ptr)->release_one(this);
            new_task_assigned = false;
        }
    }

private:
    pool_type *pool_ptr;
    std::thread real_thread;
    std::mutex m;
    std::condition_variable sig_task_assigned; //! It's unlocked to indicate that new task is ready.
    std::function<void()> task_to_issue;
    volatile bool new_task_assigned = false;
    volatile bool must_join = false;
};

class fixed_thread_pool : public fixed_object_pool<containered_thread, fixed_thread_pool *> {
public:
    fixed_thread_pool(int size) : fixed_object_pool(size, this) {}
    void join_all() {
        for(element_t &th : buffer) {
            th.join();
        }
    }    
};
using impl::fixed_thread_pool;
}


} // end namespace rlib

#endif
