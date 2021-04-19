#ifndef R_AVL_HPP_
#define R_AVL_HPP_

#include <rlib/require/cxx14>
#include <rlib/class_decorator.hpp>
#include <rlib/string/string.hpp>
#include <memory>
#include <functional>
#include <utility>

#include <rlib/stdio.hpp>

namespace avl {
    template <typename data_t, bool multi_tree = false>
    struct node {
        using this_type = node<data_t, multi_tree>;
        std::shared_ptr<this_type> left;
        std::shared_ptr<this_type> right;
        std::weak_ptr<this_type> parent;
        data_t data;
        int32_t factor = 0;
        size_t counter = 1;

#ifdef ENABLE_RAVL_FOREACH_NODE
        void for_each_node(std::function<void(const std::shared_ptr<this_type> &)> func) {
            if(left)
                left->for_each_node(func);
            if(!parent.expired()) {
                auto par = parent.lock();
                auto self_ptr = par->left;
                if(par->right.get() == this)
                    self_ptr = par->right;
                //root ignored because I can not get self_ptr

                for(size_t cter = 0; cter < counter; ++cter)
                    func(self_ptr);
            }
            if(right)
                right->for_each_node(func);
        }
#endif
    };

    template <typename data_t, bool multi_tree = false, typename data_equal_func = std::equal_to<data_t>, typename data_less_func = std::less<data_t>>
    class tree : public rlib::noncopyable {
    public:
        using this_type = tree<data_t, multi_tree, data_equal_func, data_less_func>;
        using node_type = node<data_t, multi_tree>;

        tree() = default;
        tree(this_type &&another) noexcept {
            swap(std::move(another));
        }
        this_type &operator=(this_type &&another) noexcept {
            swap(std::move(another));
            return *this;
        }

        class iterator_utils : public rlib::static_class {
        public:
            template <typename cv_node_type>
            static void next(size_t &curr_cter, std::shared_ptr<cv_node_type> &target, bool _back_tracing = false) {
                if(!target)
                    throw std::invalid_argument("Can not ++ null iterator.");
                if(_back_tracing) { //target->right already fucked.
                    if(target->parent.expired()) {
                        target.reset();
                        return;
                    }
                    auto par = target->parent.lock();
                    if(par->left && par->left == target) {
                        target = par;
                        curr_cter = 1;
                        return;
                    }
                    target = par;
                    return next(curr_cter, target, true);
                }

                if(target->counter > curr_cter) {
                    ++curr_cter;
                    return;
                }
                if(target->right) {
                    target = target->right;
                    while(target->left) target = target->left;
                    curr_cter = 1;
                    return;
                }
                else
                    return next(curr_cter, target, true);
            }

            template <typename cv_node_type>
            static void prev(size_t &curr_cter, std::shared_ptr<cv_node_type> &target, bool _back_tracing = false) {
                if(!target)
                    throw std::invalid_argument("Can not -- null iterator.");
                if(_back_tracing) { //target->left already fucked.
                    if(target->parent.expired()) {
                        target.reset();
                        return;
                    }
                    auto par = target->parent.lock();
                    if(par->right && par->right == target) {
                        target = par;
                        curr_cter = 1;
                        return;
                    }
                    target = par;
                    return prev(curr_cter, target, true);
                }

                if(target->counter > curr_cter) {
                    ++curr_cter;
                    return;
                }
                if(target->left) {
                    target = target->left;
                    while(target->right) target = target->right;
                    curr_cter = 1;
                    return;
                }
                else
                    return prev(curr_cter, target, true);
            }
        };

        class iterator {
        public:
            using this_type = iterator;
            iterator() = default;
            iterator(const std::shared_ptr<node_type> &item) : target(item) {}

            this_type &operator=(const std::shared_ptr<node_type> &item) {target = item;}

            this_type &operator++() {iterator_utils::next(curr_cter, target); return *this;}
            this_type operator++(int) {this_type backup = *this; iterator_utils::next(curr_cter, target); return backup;}
            this_type &operator--() {iterator_utils::prev(curr_cter, target); return *this;}
            this_type operator--(int) {this_type backup = *this; iterator_utils::prev(curr_cter, target); return backup;}

            data_t &operator*() {return target->data;}
            data_t *operator->() {return &target->data;}

            std::shared_ptr<node_type> to_shared() {return target;}
            operator bool() {return static_cast<bool>(target);}
        private:
            size_t curr_cter = 1;
            std::shared_ptr<node_type> target;
        };
        class reverse_iterator {
        public:
            using this_type = reverse_iterator;
            reverse_iterator() = default;
            reverse_iterator(const std::shared_ptr<node_type> &item) : target(item) {}

            this_type &operator=(const std::shared_ptr<node_type> &item) {target = item;}

            this_type &operator++() {iterator_utils::prev(curr_cter, target); return *this;}
            this_type operator++(int) {this_type backup = *this; iterator_utils::prev(curr_cter, target); return backup;}
            this_type &operator--() {iterator_utils::next(curr_cter, target); return *this;}
            this_type operator--(int) {this_type backup = *this; iterator_utils::next(curr_cter, target); return backup;}

            data_t &operator*() {return target->data;}
            data_t *operator->() {return &target->data;}

            std::shared_ptr<node_type> to_shared() {return target;}
            operator bool() {return static_cast<bool>(target);}
        private:
            size_t curr_cter = 1;
            std::shared_ptr<node_type> target;
        };
        class const_iterator {
        public:
            using this_type = const_iterator;
            const_iterator() = default;
            const_iterator(const std::shared_ptr<const node_type> &item) : target(item) {}

            this_type &operator=(const std::shared_ptr<const node_type> &item) {target = item;}

            this_type &operator++() {iterator_utils::next(curr_cter, target); return *this;}
            this_type operator++(int) {this_type backup = *this; iterator_utils::next(curr_cter, target); return backup;}
            this_type &operator--() {iterator_utils::prev(curr_cter, target); return *this;}
            this_type operator--(int) {this_type backup = *this; iterator_utils::prev(curr_cter, target); return backup;}

            const data_t &operator*() {return target->data;}
            const data_t *operator->() {return &target->data;}

            std::shared_ptr<const node_type> to_shared() {return target;}
            operator bool() {return static_cast<bool>(target);}
        private:
            size_t curr_cter = 1;
            std::shared_ptr<const node_type> target;
        };
        class const_reverse_iterator {
        public:
            using this_type = const_reverse_iterator;
            const_reverse_iterator() = default;
            const_reverse_iterator(const std::shared_ptr<const node_type> &item) : target(item) {}

            this_type &operator=(const std::shared_ptr<const node_type> &item) {target = item;}

            this_type &operator++() {iterator_utils::prev(curr_cter, target); return *this;}
            this_type operator++(int) {this_type backup = *this; iterator_utils::prev(curr_cter, target); return backup;}
            this_type &operator--() {iterator_utils::next(curr_cter, target); return *this;}
            this_type operator--(int) {this_type backup = *this; iterator_utils::next(curr_cter, target); return backup;}

            const data_t &operator*() {return target->data;}
            const data_t *operator->() {return &target->data;}

            std::shared_ptr<const node_type> to_shared() {return target;}
            operator bool() {return static_cast<bool>(target);}
        private:
            size_t curr_cter = 1;
            std::shared_ptr<const node_type> target;
        };

        iterator begin() {
            if(!root) return iterator();
            auto curr = root;
            while(curr->left)
                curr = curr->left;
            return iterator(curr);
        }
        constexpr iterator end() {
            return iterator();
        }
        reverse_iterator rbegin() {
            if(!root) return reverse_iterator();
            auto curr = root;
            while(curr->right)
                curr = curr->right;
            return reverse_iterator(curr);
        }
        constexpr reverse_iterator rend() {
            return reverse_iterator();
        }
        const_iterator cbegin() const {
            if(!root) return const_iterator();
            auto curr = std::const_pointer_cast<const node_type>(root);
            while(curr->left)
                curr = curr->left;
            return const_iterator(curr);
        }
        constexpr const_iterator cend() const {
            return const_iterator();
        }
        const_reverse_iterator crbegin() const {
            if(!root) return const_reverse_iterator();
            auto curr = std::const_pointer_cast<const node_type>(root);
            while(curr->right)
                curr = curr->right;
            return curr;
        }
        constexpr const_reverse_iterator crend() const {
            return const_reverse_iterator();
        }

        auto insert(data_t &&item, bool no_except = false) {
#ifdef ENABLE_INSERT_NULL_CHECK
            if(data_equal_func()(item, data_t()))
                throw std::invalid_argument("Sorry but you can not insert a null item.");
#endif
            std::shared_ptr<node_type> iter;
            int pos;
            std::tie(iter, pos) = do_find(item);

            if(!multi_tree && pos == 0) {
                if(no_except)
                    return iterator();
                else
                    throw std::runtime_error("Inserting duplicate element.");
            }

            ++m_size;
            if(multi_tree && pos == 0) {
                iter->counter ++;
                return iterator(iter);
            }

            auto new_node = std::make_shared<node_type>();
            new_node->data = std::move(item);

            decltype(iter->factor) iter_factor_backup;
            switch(pos) {
                case -2:
                    root = new_node;
                    break;
                case -1:
                    new_node->parent = iter;
                    iter->left = new_node;
                    iter_factor_backup = iter->factor;
                    iter->factor -= 1;
                    rebalance<true>(iter, iter_factor_backup);
                    break;
                case 1:
                    new_node->parent = iter;
                    iter->right = new_node;
                    iter_factor_backup = iter->factor;
                    iter->factor += 1;
                    rebalance<true>(iter, iter_factor_backup);
                    break;
                default:
                    throw std::runtime_error(rlib::format_string("do_find returns invalid pos {}.", pos));
            }
            return iterator(new_node);
        }
        auto insert(const data_t &item, bool no_except = false) {
            data_t copied(item);
            return insert(std::move(copied), no_except);
        }

        void erase(iterator _iter) {
            auto iter = _iter.to_shared();
            exchange_again:
            if(multi_tree && (iter->counter > 1)) {
                --iter->counter;
                --m_size;
                return;
            }

            auto to_erase = iter;
            if(iter->right) {
                to_erase = iter->right;
                while(to_erase->left)
                    to_erase = to_erase->left;
            }
            else if(iter->left) {
                to_erase = iter->left;
                while(to_erase->right)
                    to_erase = to_erase->right;
            }

            if(iter != to_erase) {
                iter->data = std::move(to_erase->data);
                if(multi_tree)
                    iter->counter = to_erase->counter;

                // fake recursion: erase(to_erase)
                iter = to_erase;
                goto exchange_again;
            }

            // do erase
            --m_size;
            if(to_erase->parent.expired())
                root.reset();
            else {
                auto par = to_erase->parent.lock();
                auto parent_factor_backup = par->factor;
                if(par->right == to_erase) {
                    par->right.reset();
                    par->factor -= 1;
                }
                else {
                    par->left.reset();
                    par->factor += 1;
                }
                rebalance<false>(par, parent_factor_backup);
            }
        }

        template <bool no_except = false>
        const_iterator find(const data_t &item) const {
            std::shared_ptr<const node_type> iter;
            int pos;
            std::tie(iter, pos) = do_find(item);

            if(no_except || pos == 0)
                return const_iterator(iter);
            else
                throw std::out_of_range("Element not found.");
        }
        template <bool no_except = false>
        iterator find(const data_t &item) {
            std::shared_ptr<node_type> iter;
            int pos;
            std::tie(iter, pos) = do_find(item);

            if(no_except || pos == 0)
                return iterator(iter);
            else
                throw std::out_of_range("Element not found.");
        }

        size_t count(const data_t &item) const noexcept {
            std::shared_ptr<const node_type> iter;
            int pos;
            std::tie(iter, pos) = do_find(item);

            if(pos != 0)
                return 0;
            if(!multi_tree)
                return 1;
            return iter->counter;
        }
        bool exist(const data_t &item) const noexcept {
            return count(item) != 0;
        }
        size_t height() const noexcept {
            size_t curr_height = 0;
            std::shared_ptr<const node_type> curr = root;
            while(curr) {
                ++curr_height;
                if(curr->factor == 1)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
            return curr_height;
        }
        size_t size() const noexcept {
            return m_size;
        }

        void swap(this_type &&another) noexcept {
            root.swap(another.root);
            std::swap(m_size, another.m_size);
        }
        void swap(this_type &another) noexcept {
            root.swap(another.root);
            std::swap(m_size, another.m_size);
        }
        void clear() noexcept {
            root.reset();
            m_size = 0;
        }

#ifdef ENABLE_RAVL_DEBUG_DUMP
        void dump() {
            // Error if data_t is not printable.
            rlib::println("root: node", root?root->data:data_t());
            for_each_node([](const std::shared_ptr<node_type> &node){
                rlib::printfln("node {}: left {} right {} parent {} factor {} counter {}", node->data, (node->left?node->left->data:data_t()), (node->right?node->right->data:data_t()),
                               (node->parent.expired()?data_t():node->parent.lock()->data), node->factor, node->counter);
            });
        }
#endif
    private:
#ifdef ENABLE_RAVL_FOREACH_NODE
        void for_each_node(std::function<void(const std::shared_ptr<node_type> &)> func) {
            if(root) {
                root->for_each_node(func);
                func(root);
            }
        }
#endif

        std::pair<std::shared_ptr<const node_type>, int/*0 if found, 1 if at right, -1 if at left, -2 if no root*/> do_find(const data_t &item) const noexcept {
            static auto is_less = data_less_func();
            static auto is_equal = data_equal_func();

            auto curr = root;
            auto return_par = root;
            auto return_pos = -2;
            while(curr) {
                if(is_equal(curr->data, item)) {
                    return {curr, 0};
                }
                return_par = curr;
                if(is_less(curr->data, item)) {
                    return_pos = 1;
                    curr = curr->right;
                }
                else {
                    return_pos = -1;
                    curr = curr->left;
                }
            }
            return {return_par, return_pos};
        }
        std::pair<std::shared_ptr<node_type>, int> do_find(const data_t &item) noexcept {
            std::pair<std::shared_ptr<const node_type>, int> &&res = static_cast<const this_type *>(this)->do_find(item);
            return std::make_pair(std::const_pointer_cast<node_type>(res.first), res.second);
        };

        template <bool is_inserting>
        int/*Return: grown_height*/ rebalance(std::shared_ptr<node_type> node, int my_factor_before_insert/*not used if |node.factor| == 2*/) {
            int grown_up = abs(node->factor) - abs(my_factor_before_insert);
            if((is_inserting && grown_up < 0) || (!is_inserting && grown_up > 0)) grown_up = 0;

            if(abs(node->factor) < 2) {
                if(grown_up != 0 && !node->parent.expired()) {
                    auto par = node->parent.lock();
                    auto par_factor_backup = par->factor;
                    par->factor += grown_up * (node == par->right ? 1 : -1); // +-1 * +-1
                    rebalance<is_inserting>(par, par_factor_backup);
                }
                return grown_up;
            }
            else if (abs(node->factor) == 2) {
                if(node->factor > 0) { // my factor is 2
                    auto child = node->right;
                    int w = child->factor;
                    if(w == -1) {
                        int w2 = child->left->factor;
                        child->left->factor = w2 == 1 ? 1 : 0;
                        child->factor = w2 == -1 ? 1 : 0;
                        node->factor = w2 == 1 ? -1 : 0;
                        rotate_to_left_2(node,child);
                        return 0;
                    }
                    rotate_to_left(node, child);
                    node->factor = 1-w;
                    child->factor = w-1;

                    if(abs(node->factor) == 2) {
                        rebalance<is_inserting>(node, 2); // Always return 0 because its factor is +-2
                    }
                    return 0;
                }
                else { // my factor is -2
                    auto child = node->left;
                    int w = child->factor;
                    if(w == 1) {
                        int w2 = child->right->factor;
                        child->right->factor = w2 == -1 ? -1 : 0;
                        child->factor = w2 == 1 ? -1 : 0;
                        node->factor = w2 == -1 ? -1 : 0;
                        rotate_to_right_2(node,child);
                        return 0; // Warn: not carefully checked.
                    }
                    node->factor = -1-w;
                    child->factor = 1+w; // 0 1
                    rotate_to_right(node, child);

                    if(abs(node->factor) == 2)
                        rebalance<is_inserting>(node, -2); // Always return 0 because its factor is +-2
                    return 0;
                }
            }
            else
                throw std::runtime_error("There's a node whose factor is greater than 2.");
        }

        //rotate without editing any bal factors.
        void rotate_to_left(std::shared_ptr<node_type> higher, std::shared_ptr<node_type> lower) {
            higher->right = lower->left;
            if(lower->left) lower->left->parent = higher;

            lower->left = higher;
            lower->parent = higher->parent;
            if(!higher->parent.expired()) {
                auto par = higher->parent.lock();
                if(higher == par->right) par->right = lower;
                else par->left = lower;
            }
            else //parent is root
                root = lower;
            higher->parent = lower;
        }
        void rotate_to_right(std::shared_ptr<node_type> higher, std::shared_ptr<node_type> lower) {
            higher->left = lower->right;
            if(lower->right) lower->right->parent = higher;

            lower->right = higher;
            lower->parent = higher->parent;
            if(!higher->parent.expired()) {
                auto par = higher->parent.lock();
                if(higher == par->right) par->right = lower;
                else par->left = lower;
            }
            else //parent is root
                root = lower;
            higher->parent = lower;
        }
        void rotate_to_left_2(std::shared_ptr<node_type> higher, std::shared_ptr<node_type> lower) {
            auto lower2 = lower->left;
            higher->right = lower2->left;
            if(lower2->left) lower2->left->parent = higher;
            lower->left = lower2->right;
            if(lower2->right) lower2->right->parent = lower;

            lower2->parent = higher->parent;
            if(!higher->parent.expired()) {
                auto par = higher->parent.lock();
                if(higher == par->right) par->right = lower2;
                else par->left = lower2;
            }
            else
                root = lower2;

            lower2->right = lower;
            lower2->left = higher;
            lower->parent = lower2;
            higher->parent = lower2;
        }
        void rotate_to_right_2(std::shared_ptr<node_type> higher, std::shared_ptr<node_type> lower) {
            auto lower2 = lower->right;
            higher->left = lower2->right;
            if(lower2->right) lower2->right->parent = higher;
            lower->right = lower2->left;
            if(lower2->left) lower2->left->parent = lower;

            lower2->parent = higher->parent;
            if(!higher->parent.expired()) {
                auto par = higher->parent.lock();
                if(higher == par->right) par->right = lower2;
                else par->left = lower2;
            }
            else
                root = lower2;

            lower2->left = lower;
            lower2->right = higher;
            lower->parent = lower2;
            higher->parent = lower2;
        }

        std::shared_ptr<node_type> root;
        size_t m_size = 0;
    };

}

#endif
