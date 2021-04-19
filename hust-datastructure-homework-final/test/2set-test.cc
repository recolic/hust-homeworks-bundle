#include "../src/lib/set.hpp"
#include <rlib/stdio.hpp>
using namespace rlib;
using namespace r;

int main() {
    avl::tree<int> t;
    t.insert(4);
    t.dump();
    t.insert(2);
    t.dump();
    t.insert(1);
    t.dump();
    t.insert(3);
    t.dump();
    t.insert(9);
    t.dump();
    t.insert(-1);
    t.dump();
    t.insert(5);
    t.dump();
    t.insert(6);
    t.dump();
    std::for_each(t.cbegin(), t.cend(), [](const int &i){rlib::println(i);});
    return 0;
}
