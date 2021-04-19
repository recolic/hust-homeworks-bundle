
#include "stdlayout_mutex.hpp"
#include "iterators.hpp"

#include <mutex>
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <list>

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <rlib/string.hpp>
#include <rlib/stdio.hpp>
#include <rlib/impl/traceable_list.hpp>

using namespace rlib::literals;
using namespace std::chrono_literals;


void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  auto ptr = mmap(NULL, size, protection, visibility, 0, 0);

  if(ptr == MAP_FAILED)
      throw std::runtime_error("mmap failed. system error: {}"_format(strerror(errno)));
  return ptr;
}

// See StackOverflow replies to this answer for important commentary about inheriting from std::allocator before replicating this code.
template <typename T>
class mmap_allocator: public std::allocator<T>
{
public:
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;

    template<typename _Tp1>
    struct rebind
    {
        typedef mmap_allocator<_Tp1> other;
    };

    pointer allocate(size_type size, const void *hint=0)
    {
        void *ptr = create_shared_memory(size + sizeof(size));
        size_t *size_ptr = reinterpret_cast<size_t *>(ptr);
        *size_ptr = size;
        return (pointer)++size_ptr;
    }

    void deallocate(pointer ptr, size_type n)
    {
        size_t *size_ptr = reinterpret_cast<size_t *>(ptr);
        --size_ptr;
        auto res = munmap(size_ptr, *size_ptr);
        if(res == -1)
            throw std::runtime_error("munmap failed. system error: {}"_format(strerror(errno)));
    }

    mmap_allocator() throw(): std::allocator<T>() {}
    mmap_allocator(const mmap_allocator &a) throw(): std::allocator<T>(a) { }
    template <class U>
    mmap_allocator(const mmap_allocator<U> &a) throw(): std::allocator<T>(a) { }
    ~mmap_allocator() throw() { }
};

class cache {
public:
    static void *operator new(size_t size) {
        void *ptr = create_shared_memory(size + sizeof(size));
        size_t *size_ptr = reinterpret_cast<size_t *>(ptr);
        *size_ptr = size;
        return ++size_ptr;
    }
    static void *operator new[](size_t size) {
        return operator new(size);
    }
    static void operator delete(void *ptr) {
        size_t *size_ptr = reinterpret_cast<size_t *>(ptr);
        --size_ptr;
        auto res = munmap(size_ptr, *size_ptr);
        if(res == -1)
            throw std::runtime_error("munmap failed. system error: {}"_format(strerror(errno)));
    }
    static void operator delete[](void *ptr) {
        return operator delete(ptr);
    }

    bool dirty = false;
    rlib::stdlayout_mutex mut;

    std::array<char, 1024> data;
    size_t data_len;

    bool eof_flag = false;
private:
};

int main() {
    std::list<cache, mmap_allocator<cache> > caches(16);

    auto pid = fork();
    if(0 == pid) {
        // child 1
        // open file to write
        std::ofstream o("./out.dat", std::ios_base::binary | std::ios_base::trunc);
        rlib::circularIterator<decltype(caches.begin())> iter(caches.begin(), caches.end(), caches.begin());
        for(;true;++iter) {
            std::lock_guard<rlib::stdlayout_mutex> lock(iter->mut);
            if(iter->dirty) {
                // write into file
                o.write(iter->data.data(), iter->data_len);
                iter->dirty = false;
            }
            if(iter->eof_flag)
                break;
        }
        rlib::println("writer exiting...");
        return 0; // fileWriter done his job!
    }
    else {
        // parent
        // open file to read data into memory
        std::ifstream i("./in.dat", std::ios::binary | std::ios::ate);
        if(not i) throw std::runtime_error("Failed to open file ./in.dat");
        size_t fileSize = i.tellg();
        i.seekg(0);
        
        rlib::circularIterator<decltype(caches.begin())> iter(caches.begin(), caches.end());
        for(;true;++iter) {
            std::unique_lock<rlib::stdlayout_mutex> lock(iter->mut);
            if(iter->dirty) {
                // Maybe: reader and writer hit their head!
                //        wait for the writer plz...
                // Maybe: reader ate its own snake tail!
                lock.unlock();
                while(iter->dirty);
                // writer finally catched...
                lock.lock();
            }

            // OK. do the file reading.
            auto blockSize = (fileSize > 1024) ? 1024 : fileSize;
            i.read(iter->data.data(), blockSize);
            iter->data_len = blockSize;
            iter->dirty = true;
            fileSize -= blockSize;
            lock.unlock();
            if(fileSize == 0) {
                iter->eof_flag = true;
                rlib::println("reader exiting...");
                return 0; // fileReader done his job!
            }
        }
    }


}



