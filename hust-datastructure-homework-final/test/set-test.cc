#include "../src/lib/set.hpp"
#include <rlib/stdio.hpp>
using namespace rlib;
using namespace r;

int main() {
//    avl::tree<int,true> t;
//    t.insert(1);
//    t.insert(2);
//    t.insert(2);
//    t.insert(2);
//    t.insert(2);
//    t.insert(3);;
//
//    std::for_each(t.cbegin(), t.cend(), [](const int &i){rlib::println(i);});
//    return 0;
    multiset<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(2);
    s.insert(2);
    s.insert(2);
    s.insert(3);
    s.insert(3);
    s.insert(3);
    s.insert(3);

    decltype(s) b;
    b.insert(6);
    b.insert(3);
    b.insert(3);
    b.insert(2);

    s.show("set1");
    b.show("set2");
    (s+b).show("join");
    (s-b).show("sub");
    (s^b).show("intersection");
}
