#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct rListNode rListNode;
typedef struct rListDescriptor rListDesc;

rListNode* rList_constructor(){
    rListNode* tmp=(rListNode*)malloc(sizeof(rListNode));
    tmp->prev=NULL;
    tmp->next=NULL;
    tmp->data=NULL;
    return tmp;
}

rListDesc* rList_newlist(){
    rListDesc* tmp=(rListDesc*)malloc(sizeof(rListDesc));
    tmp->first=NULL;
    tmp->last=NULL;
    return tmp;
}

void rList_push_back(rListDesc* desc,void* data,unsigned int length){
    if(desc->last==NULL){
        // empty list.give one.
        desc->first=rList_constructor();
        desc->last=desc->first;
        desc->last->data=malloc(length);
        memcpy(desc->last->data,data,length);
    }else{
        desc->last->next=rList_constructor();
        desc->last->next->prev=desc->last;
        desc->last->next->data=malloc(length);
        memcpy(desc->last->next->data,data,length);
        desc->last=desc->last->next;
    }
}
void rList_push_front(rListDesc* desc,void* data,unsigned int length){
    if(desc->last==NULL){
        // empty list.give one.
        desc->first=rList_constructor();
        desc->last=desc->first;
        desc->last->data=malloc(length);
        memcpy(desc->last->data,data,length);
    }else{
        desc->first->prev=rList_constructor();
        desc->first->prev->next=desc->first;
        desc->first->prev->data=malloc(length);
        memcpy(desc->first->prev->data,data,length);
        desc->first=desc->first->prev;
    }
}
void rList_pop_back(rListDesc* desc){
    if(desc->last==desc->first){
        // he is the only.
        free(desc->last->data);
        free(desc->last);
        desc->first=NULL;
        desc->last=NULL;
    }else{
        // good news encountered.
        desc->last=desc->last->prev;
        free(desc->last->next->data);
        free(desc->last->next);
        desc->last->next=NULL;
    }
}

void rList_pop_front(rListDesc* desc){
    if(desc->last==desc->first){
        // he is the only.
        free(desc->last->data);
        free(desc->last);
        desc->first=NULL;
        desc->last=NULL;
    }else{
        // good news encountered.
        desc->first=desc->first->next;
        free(desc->first->prev->data);
        free(desc->first->prev);
        desc->first->prev=NULL;
    }
}

void rList_eraseElem(rListDesc* desc,rListNode* target){
    // who is the target?
    if(target==desc->first){
        rList_pop_front(desc);
    }else if(target==desc->last){
        rList_pop_back(desc);
    }else{
        target->prev->next=target->next;
        target->next->prev=target->prev;
        free(target->data);
        free(target);
    }
}

void rList_swapElem(rListDesc* desc,rListNode* a,rListNode* b,int FLAG_POINTERSWAPPER){
    if(FLAG_POINTERSWAPPER){
        void* tmp=a->data;
        a->data=b->data;
        b->data=tmp;
    }else{
        rListNode *bprev=b->prev,*bnext=b->next;
        if(a->prev)
        a->prev->next=b;b->prev=a->prev;
        if(a->next)
        a->next->prev=b;b->next=a->next;
        if(b->prev)
        b->prev->next=a;a->prev=bprev;
        if(b->next)
        b->next->prev=a;a->next=bnext;
    }
}

void rList_destructor(struct rListDescriptor* desc){
    struct rListNode* iterator=desc->first;
    while(iterator!=NULL){
        struct rListNode* tmp=iterator->next;
        free(iterator);
        iterator=tmp;
    }
    free(desc);
}

void* rList_toArray(struct rListDescriptor* desc,int elem_size){
    // the first iteration calculates the total number of objs.
    int cnt=0;
    for(rListNode* it=desc->first;it!=NULL;it=it->next){
        cnt++;
    }
    if(!cnt) return NULL;
    void* dtarr=malloc(elem_size*cnt);
    int position=0;
    for(rListNode* it=desc->first;it!=NULL;it=it->next){
        memcpy((void *)((unsigned long)dtarr+position*elem_size),it->data,elem_size);
        position++;
    }
    return dtarr;
}
