#ifndef FUCK_MINGW_FS_FIX_HPP
#define FUCK_MINGW_FS_FIX_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

inline bool mingw_isdir(const std::string &path) {
    struct stat statbuf;
    int res = stat(path.c_str(), &statbuf);
    return res == 0 && S_ISDIR(statbuf.st_mode);
}


inline bool mingw_file_exist(const std::string &path) {
    struct stat statbuf;
    int res = stat(path.c_str(), &statbuf);
    if(res == -1 && errno == ENOENT)
        return false;
    else if(res == 0 && S_ISDIR(statbuf.st_mode))
        return false;
    else //if(S_ISREG(statbuf.st_mode) || S_ISLNK(statbuf.st_mode))
        return true;
}

#endif
