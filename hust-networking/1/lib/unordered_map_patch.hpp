#ifndef UNORDERED_MAP_PATCH_HPP
#define UNORDERED_MAP_PATCH_HPP

#include <stdexcept>
namespace std {
    template<typename key_type, typename map_type>
    inline bool unordered_map_exist_key(const map_type &map, const key_type &key) {
        try {
            map.at(key);
            return true;
        }
        catch(std::out_of_range &) {
            return false;
        }
    }
}

#endif