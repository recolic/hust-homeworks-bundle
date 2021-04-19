#ifndef HUST___REFLECTED_IMPL_HPP_
#define HUST___REFLECTED_IMPL_HPP_

/*
 * You should NEVER use this code in ANY consequence,
 *     as these code is just to make hust happy.
 */

#include <utility>
#include <functional>
#include <algorithm>
#include <vector>
#include "graph.hpp"

#include <rlib/stdio.hpp>

//class reflected_impl {
//public:
//    using data_t = int;
//    using BooleanAsserter = std::function<bool(const data_t &)>;
//    using OperationVisiter = std::function<void(const data_t &)>;
//
//    void InitList() const {}
//    void DestroyList() {container.clear();}
//    void ClearList() {container.clear();}
//    bool ListEmpty() const {return container.size() == 0;}
//    size_t ListLength() const {return container.size();}
//    data_t GetElem(size_t ___IndexPlusOne) {
//        auto index = ___IndexPlusOne - 1;
//        auto iter = container.begin();
//        for(size_t cter = 0; cter < index; ++cter) {
//            ++iter;
//        }
//        return std::move(*iter);
//    }
//    size_t _LocateElem(const BooleanAsserter &comparer) {
//        auto iter = std::find_if(container.begin(), container.end(), comparer);
//        if(iter == container.end()) {
//            return 0;
//        }
//        return LabUtils::distance(container.begin(), iter);
//    }
//    size_t LocateElem(data_t val) {
//        auto comparer = BooleanAsserter([v=val](const data_t &dat){
//            return dat == v;
//        });
//        return _LocateElem(comparer);
//    }
//    data_t PriorElem(data_t tofind) {
//        auto pos = std::find(container.begin(), container.end(), tofind);
//        if(pos == container.end() || pos == container.begin()) {
//            throw std::runtime_error("ElemError: You told me that it's undefined, so I do it.");
//        }
//        return *(--pos);
//    }
//    data_t NextElem(data_t tofind) {
//        auto pos = std::find(container.begin(), container.end(), tofind);
//        if(pos == container.end() || pos == --container.end()) {
//            throw std::runtime_error("ElemError: You told me that it's undefined, so I do it.");
//        }
//        return *(++pos);
//    }
//    void ListInsert(size_t ___IndexPlusOne, data_t elem) {
//        auto index = ___IndexPlusOne - 1;
//        auto iter = LabUtils::advance(container.begin(), index);
//        container.insert(iter, elem);
//    }
//    data_t ListDelete(size_t ___IndexPlusOne) {
//        auto index = ___IndexPlusOne - 1;
//        auto iter = LabUtils::advance(container.begin(), index);
//        auto to_return = *iter;
//        container.erase(iter);
//        return std::move(to_return);
//    }
//    void _ListTraverse(const OperationVisiter &visiter) {
//        std::for_each(container.begin(), container.end(), visiter);
//    }
//    void ListTraverse() {
//        _ListTraverse(OperationVisiter([](const auto &val){rlib::io::print(val, " ");}));
//        rlib::io::println("");
//    }
//
//    void debug() {
//        rlib::io::println_iter(container);
//        rlib::io::println(container.size());
//    }
//private:
//    Lab::list<data_t> container;
//};

//using hust_xxxx::unordered_btree;
//class reflected_impl {
//public:
//    using data_t = int;
//    using dataref_t = const data_t &;
//    using nlang = std::string;
//    using nlangref = const nlang &;
//    reflected_impl() : containers(1), current(containers.begin()) {}
//
//    void Select(size_t i) {current = containers.begin() + i;}
//    void List() {rlib::printfln("You have {} btree now, selecting {}.", containers.size(), current - containers.begin());}
//
//    void InitBiTree() {}
//    void DestroyBiTree() {containers.erase(current); current = containers.begin();}
//    void CreateBiTree() {containers.push_back(unordered_btree<data_t>());}
//    void ClearBiTree() {current->clear();}
//    bool BiTreeEmpty() {return current->empty();}
//    size_t BiTreeDepth() {return current->depth();}
//    nlang Root() {return current->_root();}
//    data_t Value(nlangref n) {return current->get(n);}
//    void Assign(nlangref n, dataref_t val) {return current->set(n, val);}
//    nlang Parent(nlangref n) {return current->parent(n);}
//    nlang LeftChild(nlangref n) {return current->lchild(n);}
//    nlang RightChild(nlangref n) {return current->rchild(n);}
//    nlang LeftSibling(nlangref n) {return current->lchild(current->parent(n));}
//    nlang RightSibling(nlangref n) {return current->rchild(current->parent(n));}
//    void InsertChild(nlangref n, size_t toInsert, size_t LR) {return current->merge(containers[toInsert], n, LR==1);}
//    void DeleteChild(nlangref n, size_t LR) {return current->drop(n, LR==1);}
//    void PreOrderTraverse() {current->for_each(unordered_btree<data_t>::printer, hust_xxxx::foreach_rule::MIDDLE_LEFT_RIGHT);}
//    void InOrderTraverse() {current->for_each(unordered_btree<data_t>::printer, hust_xxxx::foreach_rule::LEFT_MIDDLE_RIGHT);}
//    void PostOrderTraverse() {current->for_each(unordered_btree<data_t>::printer, hust_xxxx::foreach_rule::LEFT_RIGHT_MIDDLE);}
//    void LevelOrderTraverse() {current->level_for_each(unordered_btree<data_t>::printer);}
//
//private:
//    std::vector<unordered_btree<data_t>> containers;
//    decltype(containers.begin()) current;
//};

using namespace hust_xxxx;
class reflected_impl {
public:
    using data_t = int;
    using dataref_t = const data_t &;
    using lang_t = std::string;
    using langref_t = const lang_t &;
    reflected_impl() : current(containers.begin()) {}

    // __py_ccgen_begin__
    void Select(size_t i) {current = containers.begin() + i;}
    void List() {rlib::printfln("You have {} basic_graph now, selecting {}.", containers.size(), current - containers.begin());}
    void QuickTraverse() {(*current)->simple_foreach((*current)->printer);rlib::println();}
    void CreateGraph(langref_t typeStr) {containers.push_back(newFromTypeStr(typeStr));}
    void DestroyGraph() {containers.erase(current); current = containers.begin();}
    lang_t LocateVex(dataref_t val) {return (*current)->findNode(val);}
    lang_t GetVex(langref_t lang) {return (*current)->getNodeValue(lang);}
    void PutVex(langref_t lang) {(*current)->setNodeValue(lang);}
    lang_t FirstAdjVex(langref_t lang) {return (*current)->findFirstNearNode(lang);}
    lang_t NextAdjVex(langref_t lang1, langref_t lang2) {return (*current)->findNextNearNode(lang1, lang2);}
    void InsertVex(langref_t lang) {this->PutVex(lang);}
    void DeleteVex(langref_t lang) {(*current)->removeNode(lang);}
    void InsertArc(langref_t lang) {(*current)->insertEdge(lang);}
    void DeleteArc(langref_t lang) {(*current)->removeEdge(lang);}
    void DFSTraverse() {(*current)->dfs((*current)->printer);rlib::println();}
    void BFSTraverse() {(*current)->bfs((*current)->printer);rlib::println();}
    // __py_ccgen_end__

private:
    basic_graph<data_t> *newFromTypeStr(const std::string &typeStr) {
        if(typeStr == "directed_weighted_graph")
            return new directed_weighted_graph<data_t>();
        if(typeStr == "undirected_weighted_graph")
            return new undirected_weighted_graph<data_t>();
        if(typeStr == "undirected_unweighted_graph")
            return new undirected_unweighted_graph<data_t>();
        if(typeStr == "directed_unweighted_graph")
            return new directed_unweighted_graph<data_t>();
        throw std::invalid_argument("invalid typestr");
    }
    std::vector<basic_graph<data_t> *> containers;
    decltype(containers.begin()) current;
};

extern reflected_impl impl;

#endif
