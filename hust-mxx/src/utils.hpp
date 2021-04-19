#ifndef RMXX_UTILS_HPP_
#define RMXX_UTILS_HPP_ 1

#include <string>
#include <exception>
using std::stoi;
using std::string;
inline bool convertToInt(const string &s, int &out) {
    try {
        out = stoi(s);
    } catch (...) {
        return false;
    }
    return true;
}

inline bool isPrime(const int a) {
    if (a <= 1)
        return false;

    int i;
    for (i = 2; i * i <= a; i++)
        if (a % i == 0)
            return false;
    return true;
}

#include <sstream>

#ifndef _RLIB_MACRO_ENSTRING
#define _RLIB_MACRO_ENSTRING(_s) #_s
#endif

#ifndef RLIB_MACRO_TO_CSTR
#define RLIB_MACRO_TO_CSTR(m) _RLIB_MACRO_ENSTRING(m)
#endif

#define RMXX_BEGIN_MAIN \
    std::stringstream cout;
   
#define RMXX_END_MAIN(exp_num) \
    ::std::cout << cout.str(); \
    std::ofstream out_file("U201614531_" RLIB_MACRO_TO_CSTR(exp_num) ".txt", std::ios_base::out | std::ios_base::trunc); \
    if(!out_file) throw std::runtime_error("failed to open file for write."); \
    out_file << cout.str(); \
    out_file.close();

using namespace std;

#endif
