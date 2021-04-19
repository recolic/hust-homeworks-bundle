#ifndef _NETW_DUMP_FILE_HPP
#define _NETW_DUMP_FILE_HPP 1

#include <string>
#include <stdexcept>
#include <rlib/string.hpp>
#include <rlib/scope_guard.hpp>
using rlib::literals::operator""_format;

#if RLIB_OS_ID == OS_LINUX
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#else
#include <fstream>
#include <streambuf>
#endif

    static inline std::string dump_file(const std::string &fname) {
        //! I'll read the whole file before doing response. This may cause OOM for large file but it's ok for a homework.
#if RLIB_OS_ID == OS_LINUX
        auto f = open(fname.c_str(), O_RDONLY);
        if(f == -1)
            throw std::runtime_error("Open file {}: {}"_format(fname, strerror(errno)));
        rlib_defer([&](){close(f);});
        auto len = lseek(f, 0, SEEK_END);
        lseek(f, 0, SEEK_SET);
        void *dataptr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, f, 0);
        if(dataptr == MAP_FAILED)
            throw std::runtime_error("Open file {}: {}"_format(fname, strerror(errno)));
        return std::string((char *)dataptr, len);
#else
        std::ifstream f(fname);
        if(!f) {
            throw std::runtime_error("Open file {} failed."_format(fname));
        }
        return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
#endif
    }

#endif //_NETW_DUMP_FILE_HPP
