#include <list.h>

/* The Linux Kernel list library
 *
     LIST_EMPTY(LIST_HEAD *head);

     LIST_ENTRY(TYPE);

     LIST_FIRST(LIST_HEAD *head);

     LIST_FOREACH(TYPE *var, LIST_HEAD *head, LIST_ENTRY NAME);

     LIST_HEAD(HEADNAME, TYPE);

     LIST_HEAD_INITIALIZER(LIST_HEAD head);

     LIST_INIT(LIST_HEAD *head);

     LIST_INSERT_AFTER(TYPE *listelm, TYPE *elm, LIST_ENTRY NAME);

     LIST_INSERT_BEFORE(TYPE *listelm, TYPE *elm, LIST_ENTRY NAME);

     LIST_INSERT_HEAD(LIST_HEAD *head, TYPE *elm, LIST_ENTRY NAME);

     LIST_NEXT(TYPE *elm, LIST_ENTRY NAME);

     LIST_REMOVE(TYPE *elm, LIST_ENTRY NAME);

     LIST_SWAP(LIST_HEAD *head1, LIST_HEAD *head2, TYPE, LIST_ENTRY NAME);
 */
 
// Interface provided by me
namespace r {
    using element_type = int;

    struct list_node {
        struct list_head managed;
        element_type data;
    };

    struct mStack {
        struct list_node m_list; 
        int size;

        int unused_m;
    };

    void init(mStack &self) {
        INIT_LIST_HEAD(&self.m_list.managed);
    }
    void setUnusedM(mStack &self, int m) {
        self.unused_m = m;
    }
    int getUnusedM(const mStack &self) {
        return self.unused_m;
    }
    void copyAssign(mStack &self, const mStack &src) {
        
    }
    void getSize(const mStack &self) {
    
    }
    void at(const mStack &self, int index) {
        // O(n). but do not mind it.
    }
    void push_front(mStack &self, element_type element) {
        list_node tmp;
        tmp.data = element;
        list_add(&tmp.managed, &mStack.m_list.managed);
    }
    element_type front(const mStack &self) {
        
    }
    void pop_front(mStack &self) {
    
    }
    std::string to_string(const mStack &self) {
    
    }
    void clear(mStack &self) {
    
    }
}

using STACK = r::mStack;

///////////////////////////// WARNING: Polluting global namespace. Be caution!
// Interface required by Ma
void initSTACK(STACK *const p, int m) {
    r::init(*p);
    r::setUnusedM(*p, m);
}
void initSTACK(STACK *const p, const STACK&s) {
    r::init(*p);
    r::copyAssign(*p, s);
}
int size (const STACK *const p) {
    return r::getUnusedM(*p);
}
int  howMany (const STACK *const p) {
    return r::getSize(*p);
}
int  getelem (const STACK *const p, int x) {
    return r::at(*p, x);
}
STACK *const push(STACK *const p, int e) {
    r::push_front(*p, e);
    return p;
}
STACK *const pop(STACK *const p, int &e) {
    e = r::front(*p);
    r::pop_front(*p);
    return p;
}
STACK *const assign(STACK*const p, const STACK&s) {
    r::copyAssign(*p, s);
    return p;
}
void print(const STACK*const p) {
    std::cout << r::to_string(*p) << std::endl;
}
void destroySTACK(STACK*const p) {
    r::clear(*p);
}
///////////////////////////// Dirty area end


#include <rlib/opt.hpp>

