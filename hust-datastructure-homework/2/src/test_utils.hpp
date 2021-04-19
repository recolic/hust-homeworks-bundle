#include <cstdlib>
#include <rlib/stdio.hpp>
#include <rlib/traits.hpp>

#define dynamic_assert(cond, message) do { \
        if(!cond) { \
            rlib::io::println("dynamic assertion failed:", message); \
            std::exit(2); \
        } \
    } while(false)

// -- operation must be a templated callable object, usually templated lambda.
// NEW: operation must fuck two buf at same time.
#define ASSERT_EQUIVALENCE(bufA, bufB, operation, equal_checker) \
    do { \
        static_assert(std::is_same<rlib::is_callable<decltype(equal_checker<double>)>::type, \
                    std::true_type>::value, \
                    "equal_checker is not callable"); \
        dynamic_assert(equal_checker(bufA, bufB), "given buf is not equal."); \
        operation(bufA, bufB); \
        dynamic_assert(equal_checker(bufA, bufB), "operation failed."); \
    } while(false)
/*
//vector
#include "lab_vector.hpp"
#include <vector>

template<typename data_t>
bool vector_equal(const Lab::vector<data_t> &vcta, const std::vector<data_t> &vctb)
{
    if(vcta.size() != vctb.size()) return false;
    Lab::vector<data_t> &fake_vcta = const_cast<Lab::vector<data_t> &>(vcta);
    for(auto ia = fake_vcta.begin(), ib = vctb.begin();
        ia != fake_vcta.end() && ib != vctb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
        }
    return true;
}
#define VECTOR_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, vector_equal)
*/
//list
#include "lab_list.hpp"
#include <list>

template<typename data_t>
bool list_equal(const Lab::list<data_t> &bufa, const std::list<data_t> &bufb)
{
    if(bufa.size() != bufb.size()) return false;
    Lab::list<data_t> &fake_bufa = const_cast<Lab::list<data_t> &>(bufa);
    for(auto ia = fake_bufa.begin(), ib = bufb.begin();
        ia != fake_bufa.end() && ib != bufb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
        }
    return true;
}
#define LIST_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, list_equal)
/*
//set
#include "lab_set.hpp"
#include <set>

template<typename data_t>
bool set_equal(const Lab::set<data_t> &bufa, const std::set<data_t> &bufb)
{
    if(bufa.size() != bufb.size()) return false;
    Lab::set<data_t> &fake_bufa = const_cast<Lab::set<data_t> &>(bufa);
    for(auto ia = fake_bufa.begin(), ib = bufb.begin();
        ia != fake_bufa.end() && ib != bufb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
        }
    return true;
}
#define SET_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, set_equal)

//priority_queue
#include "lab_priority_queue.hpp"
#include <queue>

template<typename data_t>
bool priority_queue_equal(const Lab::priority_queue<data_t> &bufa, const std::priority_queue<data_t> &bufb)
{
    return true;
}
#define PRIORITY_QUEUE_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, priority_queue_equal)
template<typename data_t>
bool priority_queue_destroy_and_check(Lab::priority_queue<data_t> &bufa, std::priority_queue<data_t> &bufb)
{
    if(bufa.size() != bufb.size()) return false;
    while(bufb.size())
    {
        if(bufa.top() != bufb.top()) return false;
        bufa.pop();
        bufb.pop();
    }
    return true;
}

//unordered_map
#include "lab_unordered_map.hpp"
#include <unordered_map>

template<typename key_t, typename data_t>
bool unordered_map_equal(const Lab::unordered_map<key_t, data_t> &bufa, const std::unordered_map<key_t, data_t> &bufb)
{
    if(bufa.size() != bufb.size()) return false;
    Lab::unordered_map<key_t, data_t> &fake_bufa = const_cast<Lab::unordered_map<key_t, data_t> &>(bufa);
    for(auto ia = fake_bufa.begin(), ib = bufb.begin();
        ia != fake_bufa.end() && ib != bufb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
            if(fake_bufa.find((*ib).first) != ia) return false;
        }
    return true;
}
template<typename key_data_t>
bool _unordered_map_equal(const Lab::unordered_map<key_data_t, key_data_t> &bufa, const std::unordered_map<key_data_t, key_data_t> &bufb)
{
    return unordered_map_equal(bufa, bufb);
}
#define UNORDERED_MAP_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, _unordered_map_equal)

*/