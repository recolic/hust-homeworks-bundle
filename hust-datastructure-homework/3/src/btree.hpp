#ifndef HUST_BTREE_HPP_
#define HUST_BTREE_HPP_

//#include <gc.h> //You cannot compile it and it doesn't matter.
#include <rlib/require/cxx11>
#include <stdexcept>
#include <exception>
#include <functional>

#include <rlib/string/string.hpp>
#include <rlib/stdio.hpp>

namespace hust_xxxx {
    enum class foreach_rule {LEFT_MIDDLE_RIGHT, LEFT_RIGHT_MIDDLE, MIDDLE_LEFT_RIGHT};

    template<typename data_t>
    class [[deprecated/*, "fatal memory bug, invalid algo, extremely bad design."*/]] unordered_btree {
        struct node {
            data_t payload;
            node *left = nullptr;
            node *right = nullptr;
            node *parent = nullptr;
            size_t depth = 0; //Root
            node() = delete;
            node(const data_t &payload, node *parent) : payload(payload), parent(parent), depth(parent?parent->depth+1:0) {}

            void for_each(foreach_rule rule, std::function<void(node &)> func) {
                if(rule == foreach_rule::MIDDLE_LEFT_RIGHT) func(*this);
                if(left) left->for_each(rule, func);
                if(rule == foreach_rule::LEFT_MIDDLE_RIGHT) func(*this);
                if(right) right->for_each(rule, func);
                if(rule == foreach_rule::LEFT_RIGHT_MIDDLE) func(*this);
            }
        };

    public:
        using nlang = std::string;
        unordered_btree() {}

        bool empty() const {
            return root == nullptr;
        }
        bool clear() {
            root = nullptr;
        }
        size_t depth() {
            size_t max_depth = 0;
            this->for_each([&max_depth](node &n){
                max_depth = n.depth>max_depth ? n.depth : max_depth;
            });
            return max_depth;
        }
        nlang _root() {
            return std::move(nlang(""));
        }
        data_t get(const nlang &pos) {
            auto n = nlang_translate(pos);
            if(!n)
                throw std::runtime_error("Trying to access an empty node.");
            return std::move(n->payload);
        }
        void set(const nlang &pos, const data_t &payload) {
            auto iter = nlang_translate(pos);
            if(iter)
                iter->payload = payload;
            else
                nlang_translate(pos, true, payload);
        }
        nlang parent(nlang pos) {
            rlib::replaceSubString(pos, " ", "");
            return pos.empty() ? pos : pos.substr(0, pos.size()-1);
        }
        nlang lchild(const nlang &pos) {
            return pos + 'L';
        }
        nlang rchild(const nlang &pos) {
            return pos + 'R';
        }
        void for_each(std::function<void(node &)> func, typename hust_xxxx::foreach_rule rule = foreach_rule::LEFT_MIDDLE_RIGHT) {
            if(root) root->for_each(rule, func);
        }
        void level_for_each(std::function<void(node &)> func) {
            size_t curr_depth = 0;
            while(true) {
                bool must_break = true;
                this->for_each([&, _curr_depth=curr_depth](node &n){
                    if(n.depth == _curr_depth) {
                        func(n);
                        must_break = false;
                    }
                });                
                if(must_break) break;
                ++curr_depth;
            }
        }
        static void printer(node &n) {rlib::print(n.payload, "");}
        void merge(unordered_btree &another, const nlang &where, bool right) {
            auto n = nlang_translate(where);
            if(right) n->right = another.root;
            else n->left = another.root;
            another.root = nullptr;
        }
        void drop(const nlang &where, bool right) {
            auto n = nlang_translate(where);
            if(right) n->right = nullptr;
            else n->left = nullptr;
        }

    private:
        node *nlang_translate(const nlang &lang, bool newIfNull = false, const data_t &newPayload = data_t()) {
            node *curr = root;
            for(auto act : lang) {
                if(!curr)
                    throw std::runtime_error("invalid nlang to this tree. Too many null in path.");
                switch(act) {
                case 'L':
                    if(!curr->left)
                        curr->left = new node(newPayload, curr);
                    curr = curr->left;
                    break;
                case 'R':
                    if(!curr->right)
                        curr->right = new node(newPayload, curr);
                    curr = curr->right;
                    break;
                case ' ':
                    break;
                default:
                    throw std::runtime_error("invalid nlang to this tree.");
                }
            }
            if(!curr && newIfNull) //Create root.
                root = new node(newPayload, nullptr);
            return curr;
        }
        node *root = nullptr;
    };
}



#endif