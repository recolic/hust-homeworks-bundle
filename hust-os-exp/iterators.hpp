#ifndef RLIB_ITERATOR_HPP_
#define RLIB_ITERATOR_HPP_ 1

namespace rlib {
template <class baseIter>
class circularIterator {
    private:
        baseIter cur;
        baseIter begin;
        baseIter end;
    public:
        circularIterator(baseIter b, baseIter e)
            :cur(b), begin(b), end(e) {}
        circularIterator(baseIter b, baseIter e, baseIter c)
            :cur(c), begin(b), end(e) {}

        baseIter & operator ++() {++cur; if(cur == end) {cur = begin;} return cur;}
        typename baseIter::pointer operator ->() {return &*cur;}
        typename baseIter::reference operator *() {return *cur;}
};
}

#endif
