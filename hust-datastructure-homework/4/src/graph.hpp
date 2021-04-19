#ifndef HUST_XXXX_GRAPH_HPP_
#define HUST_XXXX_GRAPH_HPP_

#include <gc/gc.h>
#include <rlib/string/string.hpp>

#include <list>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <exception>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>

// Warning: namespace pollution
using namespace std::string_literals;

namespace hust_xxxx {
    template <typename data_t>
    class basic_graph : public GCObject {
    public:
        using weight_t = uint32_t;
        struct node_t;
        using edge_t = std::pair<node_t *, weight_t>;
        struct node_t : public GCObject {
            node_t() = default;
            explicit node_t(const data_t &dat) : dat(dat) {}
            data_t dat;
            std::vector<edge_t> neighbors;
        };

#ifdef COMPILE_NO_ERASE
#ifndef NODES_PRE_ALLOC_MEM
#define NODES_PRE_ALLOC_MEM 10000000
#endif
        basic_graph() {nodes.reserve(NODES_PRE_ALLOC_MEM);}
#else
        basic_graph() = default;
#endif
        virtual ~basic_graph() = default;

    protected:
        template <typename _data_t>
        static _data_t stringToDataObj(const std::string &str) {
            std::stringstream ss;
            _data_t val;
            ss << str;
            ss >> val;
            return std::move(val);
        }
        static std::string dataObjToString(const data_t &dat) {
            std::stringstream ss;
            ss << dat;
            return std::move(ss.str());
        }
        std::string deAlias(const std::string &addr) {
            if(addr.empty())
                return addr;
            try {
                return nodeAlias.at(addr);
            }
            catch (std::out_of_range &) {
                return addr;
            }
        }
        std::string toNodeLanguage(const node_t &node) {
            return std::move(rlib::format_string("{}`{}{}{}", node.dat, std::hex, (uint64_t)(&node), std::dec));
        }
        std::string toEdgeLanguage(const node_t &from, const edge_t &to) {
            return std::move(rlib::format_string("{}`{}{}`{}{}", to.second, std::hex, (uint64_t)&from, (uint64_t)&to.first, std::dec));
        }
        auto fromNodeLanguage(const std::string &lang, bool newIfInvalidAddr = false, bool assignIfNew = false, bool assignIfExist = false) {
            auto datAndAddr = rlib::splitString(lang, '`');
            if(datAndAddr.size() != 2)
                throw std::invalid_argument("fromNodeLanguage want a nodeLanguage with address, but got bad format.");
            data_t val = stringToDataObj<data_t>(datAndAddr[0]);
            static_assert(std::is_same<uint64_t, unsigned long>::value, "unsigned long isn't uint64_t");
            try {
                uint64_t addr = std::stoul(deAlias(datAndAddr[1]), nullptr, 16);
                auto target = nodes.end();
                try {
                    target = nodePointerToIter(reinterpret_cast<node_t *>(addr));
                }
                catch(std::invalid_argument &) {}

                if(target != nodes.end()) {
                    if(assignIfExist)
                        target->dat = val;
                    return target;
                }
            }
            catch(std::invalid_argument &) {
                // invalid addr, continue to try append.
            }
            catch(std::out_of_range &e) {
                // seems valid addr, but out of range.
                throw std::out_of_range(rlib::format_string("Address `{}` out_of_range, check it!(stoul says {})", datAndAddr[1], e.what()));
            }

            if(!newIfInvalidAddr)
                throw std::invalid_argument(rlib::format_string("Can not find node_t at {}{}", std::hex, datAndAddr[1]));
            if(assignIfNew)
                nodes.push_back(node_t(val));
            else
                nodes.push_back(node_t());
            if(!datAndAddr[1].empty()) {
                nodeAlias[datAndAddr[1]] = rlib::format_string("{}{}{}", std::hex, (uint64_t)&*--nodes.end(), std::dec);//std::to_string(reinterpret_cast<uint64_t>(&*(--nodes.end())));
            } //appointed alias
            return --nodes.end();
        }

        auto fromEdgeLanguage(const std::string &lang, bool newIfInvalidAddr = false) {
            auto arg = rlib::splitString(lang, '`');
            if(arg.size() != 3)
                throw std::invalid_argument("bad edge language");
            weight_t val = stringToDataObj<weight_t>(arg[0]);
            static_assert(std::is_same<uint64_t, unsigned long>::value, "unsigned long isn't uint64_t");
            node_t *addrFrom = reinterpret_cast<node_t *>(std::stoul(deAlias(arg[1]), nullptr, 16));
            node_t *addrTo = reinterpret_cast<node_t *>(std::stoul(deAlias(arg[2]), nullptr, 16));

            auto target = nodePointerToIter(addrFrom); //throws std::invalid_argument
            nodePointerToIter(addrTo); //Confirm that nodeTo do exists.

            auto pos = std::find_if(target->neighbors.begin(), target->neighbors.end(), [&](const edge_t &e){
                return (uint64_t)addrTo == (uint64_t)e.first;
            });
            if(pos != target->neighbors.end()) {
                return pos;
            }
            else {
                if(newIfInvalidAddr) {
                    target->neighbors.push_back(std::make_pair(addrTo, val));
                    return target->neighbors.end() - 1;
                }
                else
                    throw std::invalid_argument("requested edge not exist");
            }
        }

// For std::vector<>, O(1) convert...
#ifdef COMPILE_NO_ERASE
        size_t nodePointerToIndex(const node_t *ptr) {
            node_t *begin = nodes.data();
            if(ptr - begin >= nodes.size() * sizeof(node_t) || ptr - begin < 0)
                throw std::invalid_argument("nodePointerToIter failed: not found.");
            return ptr - begin;
        }
        auto nodePointerToIter(const node_t *ptr) {
            return nodes.begin() + nodePointerToIndex(ptr);
        }
#else
        //Warning: O(n) is too slow!
        size_t nodePointerToIndex(const node_t *ptr) {
            size_t cter = 0;
            for(auto iter = nodes.begin(); iter != nodes.end(); ++iter, ++cter) {
                if(&*iter == ptr)
                    return cter;
            }
            throw std::invalid_argument("nodePointerToIndex failed: node not found.");
        }
        //Warning: O(n) is too slow!
        auto nodePointerToIter(const node_t *ptr) {
            for(auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
                if(&*iter == ptr)
                    return iter;
            }
            throw std::invalid_argument("nodePointerToIndex failed: node not found.");
        }
#endif
    public:
        std::string findNode(const data_t &val) {
            for(auto &node : nodes) {
                if(node.dat == val)
                    return toNodeLanguage(node);
            }
            return "`";
        }
        std::string getNodeValue(const std::string &lang) {
            return toNodeLanguage(*fromNodeLanguage(lang));
        }
        void setNodeValue(const std::string &lang) {
            fromNodeLanguage(lang, true, true, true);
        }
        std::string findFirstNearNode(const std::string &lang) {
            auto node = fromNodeLanguage(lang);
            return node->neighbors.empty() ? "`" : toNodeLanguage(*node->neighbors.begin()->first);
        }
        std::string findNextNearNode(const std::string &centerNd, const std::string &posNd) {
            auto center = fromNodeLanguage(centerNd);
            auto pos = fromNodeLanguage(posNd);
            for(auto iter = center->neighbors.begin(); iter != center->neighbors.end(); ++iter) {
                if (iter->first == &*pos) {
                    ++iter;
                    if(iter == center->neighbors.end())
                        return "`";
                    else
                        return toNodeLanguage(*iter->first);
                }
            }
            return "`";
        }
        void removeNode(const std::string &lang) {
#ifdef COMPILE_NO_ERASE
            throw std::runtime_error("This program is compiled as vector version, which gets much higher performance but without supporting removeNode.");
#else
            nodes.erase(fromNodeLanguage(lang));
#endif
        }

        using node_visiter = std::function<void(node_t &)>;
        const node_visiter printer = [](node_t &nd){rlib::printf("{}`{}{}{} ", nd.dat, std::hex, (uint64_t)&nd, std::dec);};
        void dfs(const node_visiter &func) {
            std::vector<bool> masks(nodes.size(), false);
            dfs_helper(func, masks, *nodes.begin());
        }
        void dfs_helper(const node_visiter &func, std::vector<bool> &masks, node_t &curr) {
            masks[nodePointerToIndex(&curr)] = true;
            func(curr);
            for(auto &edge : curr.neighbors) {
                node_t &next = *edge.first;
                size_t index = nodePointerToIndex(&next);
                if(!masks[index])
                    dfs_helper(func, masks, next);
            }
        }
        void bfs(const node_visiter &func) {
            std::vector<bool> masks(nodes.size(), false);
            masks[0] = true; //dfs method can't apply to bfs.
            bfs_helper(func, masks, std::list<node_t *>{&*nodes.begin()});
        }
        void bfs_helper(const node_visiter &func, std::vector<bool> &masks, const std::list<node_t *> &curr) {
            std::list<node_t *> next;
            for(node_t *node : curr) {
                for(auto &edge : node->neighbors) {
                    node_t &nextNode = *edge.first;
                    size_t index = nodePointerToIndex(&nextNode);
                    if(masks[index])
                        continue;
                    else {
                        masks[index] = true;
                        next.push_back(&nextNode);
                    }
                }
            }
            std::for_each(curr.begin(), curr.end(), [&func](node_t *p){func(*p);});
            if(!next.empty())
                bfs_helper(func, masks, next);
        }
        void simple_foreach(const node_visiter &func) {
            std::for_each(nodes.begin(), nodes.end(), func);
        }

        virtual void insertEdge(const std::string &lang) = 0;
        virtual void removeEdge(const std::string &lang) = 0;
    protected:
#ifdef COMPILE_NO_ERASE
        std::vector<node_t> nodes;
#else
        std::list<node_t> nodes;
#endif
        std::unordered_map<std::string, std::string> nodeAlias;
    };


    template <typename data_t>
    class directed_weighted_graph : public basic_graph<data_t> {
    public:
        using super = basic_graph<data_t>;
        directed_weighted_graph() = default;
        virtual ~directed_weighted_graph() = default;

        virtual void insertEdge(const std::string &lang) override {
            super::fromEdgeLanguage(lang, true);
        }
        virtual void removeEdge(const std::string &lang) override {
            auto nodeLang = "`"s + rlib::splitString(lang, '`')[1];
            super::fromNodeLanguage(nodeLang)->neighbors.erase(super::fromEdgeLanguage(lang));
        }
    };

    template <typename data_t>
    class undirected_weighted_graph : public directed_weighted_graph<data_t> {
    public:
        undirected_weighted_graph() = default;
        virtual ~undirected_weighted_graph() = default;

        virtual void insertEdge(const std::string &lang) override {
            auto parts = rlib::splitString(lang, '`');
            std::string reversedLang = rlib::joinString('`', std::array<std::string, 3>{parts[0], parts[2], parts[1]});
            directed_weighted_graph<data_t>::insertEdge(lang);
            directed_weighted_graph<data_t>::insertEdge(reversedLang);
        }
        virtual void removeEdge(const std::string &lang) override {
            auto parts = rlib::splitString(lang, '`');
            std::string reversedLang = rlib::joinString('`', std::array<std::string, 3>{parts[0], parts[2], parts[1]});
            directed_weighted_graph<data_t>::removeEdge(lang);
            directed_weighted_graph<data_t>::removeEdge(reversedLang);
        }
    };

    template <typename data_t>
    class directed_unweighted_graph : public directed_weighted_graph<data_t> {
    public:
        directed_unweighted_graph() = default;
        virtual ~directed_unweighted_graph() = default;

        virtual void insertEdge(const std::string &lang) override {
            auto parts = rlib::splitString(lang, '`');
            parts[0] = '1';
            directed_weighted_graph<data_t>::insertEdge(rlib::joinString('`', parts));
        }
    };

    template <typename data_t>
    class undirected_unweighted_graph : public undirected_weighted_graph<data_t> {
    public:
        undirected_unweighted_graph() = default;
        virtual ~undirected_unweighted_graph() = default;

        virtual void insertEdge(const std::string &lang) override {
            auto parts = rlib::splitString(lang, '`');
            parts[0] = '1';
            undirected_weighted_graph<data_t>::insertEdge(rlib::joinString('`', parts));
        }
    };
}





#endif