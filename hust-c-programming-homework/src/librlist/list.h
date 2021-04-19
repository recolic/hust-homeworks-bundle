#ifndef R_LIST_EXTENDC
#define R_LIST_EXTENDC

struct rListNode{
    struct rListNode* prev;
    struct rListNode* next;
    void* data;
};

struct rListDescriptor{
    struct rListNode* first;
    struct rListNode* last;
};

// with no strict complexity limitation,this implementation is very inefficient.
// just for hust c homework. never use this in production environment.

struct rListNode* rList_constructor();
struct rListDescriptor* rList_newlist();
void rList_push_back(struct rListDescriptor* desc,void* data,unsigned int length);
void rList_pop_back(struct rListDescriptor* desc);
void rList_push_front(struct rListDescriptor* desc,void* data,unsigned int length);
void rList_pop_front(struct rListDescriptor* desc);
void rList_eraseElem(struct rListDescriptor* desc,struct rListNode* target);
void rList_swapElem(struct rListDescriptor* desc,struct rListNode* a,struct rListNode* b,int FLAG_POINTERSWAPPER);
void rList_destructor(struct rListDescriptor* desc);
void* rList_toArray(struct rListDescriptor* desc,int elem_size);

typedef struct rListDescriptor rListDescriptor;
typedef struct rListNode* rListIterator;

typedef rListDescriptor *rList;

#define rList_for_each(_var_iterator, _var_list) for(rListIterator _var_iterator = _var_list->first; _var_iterator != nullptr; _var_iterator = _var_iterator->next)

#endif