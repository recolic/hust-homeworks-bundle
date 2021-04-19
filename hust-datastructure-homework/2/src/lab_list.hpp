#ifndef LAB_LIST_HPP_
#define LAB_LIST_HPP_

#include <cstddef>
#include <iterator>
namespace Lab
{
    template<typename Type>
    class list
    {
    private:
        struct node
        {
            node() = default;
            node(const Type &data, node *pre, node *next) : data(data), pre(pre), next(next) {}
            Type data = 0;
            node *pre = nullptr;
            node *next = nullptr;
        };

    public:
        class iterator :
                public std::iterator<std::bidirectional_iterator_tag, Type, Type, const Type *, Type &>
        {
        public:
            iterator(node *currentTmp) { current = currentTmp; }

            Type &operator*() { return current->data; }

            const Type &operator*() const { return current->data; }

            iterator &operator++()
            {
                current = current->next;
                return *this;
            }

            iterator &operator--()
            {
                current = current->pre;
                return *this;
            }

            iterator &operator++(int)
            {
                auto restore = *this;
                current = current->next;
                return restore;
            }

            iterator &operator--(int)
            {
                auto restore = *this;
                current = current->pre;
                return restore;
            }

            bool operator!=(const iterator &another) const
            {
                return another.current != current;
            }

            bool operator==(const iterator &another) const
            {
                return another.current == current;
            }

            node *current;
        };

        void push_back(const Type &elem);

        void push_front(const Type &elem);

        iterator begin();

        iterator end();

        size_t size() const;

        void pop_front();

        void pop_back();

        void insert(iterator iter, const Type &elem);

        void erase(iterator iter);

        void clear();

        ~list();

    private:
        node *beg = nullptr;
        node *en = nullptr;
        size_t length = 0;
    };

    template<typename Type>
    typename list<Type>::iterator list<Type>::begin()
    {
        return iterator(beg);
    }

    template<typename Type>
    typename list<Type>::iterator list<Type>::end()
    {
        return iterator(en);
    }

    template<typename Type>
    void list<Type>::push_back(const Type &elem)
    {
        node *newNode = new node;
        newNode->data = elem;
        newNode->pre = en;
        newNode->next = nullptr;
        if (en)
        {
            en->next = newNode;
        }
        en = newNode;
        if (!length)
        {
            beg = newNode;
        }
        length++;
    }

    template<typename Type>
    void list<Type>::push_front(const Type &elem)
    {
        node *newNode = new node;
        newNode->data = elem;
        newNode->next = beg;
        newNode->pre = nullptr;
        if (beg)
        {
            beg->pre = newNode;
        }
        beg = newNode;
        if (!length)
            en = newNode;
        length++;
    }

    template<typename Type>
    size_t list<Type>::size() const { return length; }

    template<typename Type>
    void list<Type>::pop_front()
    {
        node *newNode = new node;
        newNode = beg;
        beg = beg->next;
        if (beg)
            beg->pre = nullptr;
        length--;
        delete newNode;
    }

    template<typename Type>
    void list<Type>::pop_back()
    {
        node *newNode = new node;
        length--;
        newNode = en;
        en = en->pre;
        if (en)
            en->next = nullptr;
        delete newNode;
    }

    template<typename Type>
    void list<Type>::insert(iterator iter, const Type &elem)
    {
        if(iter == this->end()) return this->push_back(elem);
        if(iter == this->begin()) return this->push_front(elem);

        node *newNode = new node{elem, iter.current->pre, iter.current};
        iter.current->pre->next = newNode;
        iter.current->pre = newNode;
        length++;
    }

    template<typename Type>
    void list<Type>::erase(iterator iter)
    {
        // node *newNode = iter.current->pre;
        if (iter.current->pre)
            iter.current->pre->next = iter.current->next;
        if (iter.current->next)
            iter.current->next->pre = iter.current->pre;
        delete iter.current;
        length--;
    }

    template<typename Type>
    void list<Type>::clear()
    {
        while (beg != en)
        {
            node *newNode = beg->next;
            delete beg;
            beg = newNode;
            length--;
        }
        delete beg;
        beg = en = nullptr;
        length = 0;
    }

    template<typename Type>
    list<Type>::~list()
    {
        this->clear();
    }
} // namespace Lab

#endif