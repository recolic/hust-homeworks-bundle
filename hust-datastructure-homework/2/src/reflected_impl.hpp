#ifndef HUST___REFLECTED_IMPL_HPP_
#define HUST___REFLECTED_IMPL_HPP_

/*
 * You should NEVER use this code in ANY consequence,
 *     as these code is just to make hust happy.
 */

#include <utility>
#include <functional>
#include <algorithm>
#include "lab_list.hpp"
#include "labafx.hpp"

#include <rlib/stdio.hpp>

class reflected_impl {
public:
    using data_t = int;
    using BooleanAsserter = std::function<bool(const data_t &)>;
    using OperationVisiter = std::function<void(const data_t &)>;

    void InitList() const {}
    void DestroyList() {container.clear();}
    void ClearList() {container.clear();}
    bool ListEmpty() const {return container.size() == 0;}
    size_t ListLength() const {return container.size();}
    data_t GetElem(size_t ___IndexPlusOne) {
        auto index = ___IndexPlusOne - 1;
        auto iter = container.begin();
        for(size_t cter = 0; cter < index; ++cter) {
            ++iter;
        }
        return std::move(*iter);
    }
    size_t _LocateElem(const BooleanAsserter &comparer) {
        auto iter = std::find_if(container.begin(), container.end(), comparer);
        if(iter == container.end()) {
            return 0;
        }
        return LabUtils::distance(container.begin(), iter);
    }
    size_t LocateElem(data_t val) {
        auto comparer = BooleanAsserter([v=val](const data_t &dat){
            return dat == v;
        });
        return _LocateElem(comparer);
    }
    data_t PriorElem(data_t tofind) {
        auto pos = std::find(container.begin(), container.end(), tofind);
        if(pos == container.end() || pos == container.begin()) {
            throw std::runtime_error("ElemError: You told me that it's undefined, so I do it.");
        }
        return *(--pos);
    }
    data_t NextElem(data_t tofind) {
        auto pos = std::find(container.begin(), container.end(), tofind);
        if(pos == container.end() || pos == --container.end()) {
            throw std::runtime_error("ElemError: You told me that it's undefined, so I do it.");
        }
        return *(++pos);
    }
    void ListInsert(size_t ___IndexPlusOne, data_t elem) {
        auto index = ___IndexPlusOne - 1;
        auto iter = LabUtils::advance(container.begin(), index);
        container.insert(iter, elem);
    }
    data_t ListDelete(size_t ___IndexPlusOne) {
        auto index = ___IndexPlusOne - 1;
        auto iter = LabUtils::advance(container.begin(), index);
        auto to_return = *iter;
        container.erase(iter);
        return std::move(to_return);
    }
    void _ListTraverse(const OperationVisiter &visiter) {
        std::for_each(container.begin(), container.end(), visiter);
    }
    void ListTraverse() {
        _ListTraverse(OperationVisiter([](const auto &val){rlib::io::print(val, " ");}));
        rlib::io::println("");
    }

    void debug() {
        rlib::io::println_iter(container);
        rlib::io::println(container.size());
    }
private:
    Lab::list<data_t> container;
};

extern reflected_impl impl;

#endif
