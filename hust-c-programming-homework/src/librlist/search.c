#include "search.h"
#define NULL 0

rListIterator rList_search(rListDescriptor *desc,int (*is_match)(void* item,void* extra_args),void* extra_args){
    for(rListIterator it=desc->first;it!=NULL;it=it->next){
        if(is_match(it->data,extra_args)) return it;
    }
    return NULL;
}
rListDescriptor* rList_multisearch(rListDescriptor* desc,int (*is_match)(void* item,void* extra_args),void* extra_args,int elem_size){
    rListDescriptor* result=rList_newlist();
    for(rListIterator it=desc->first;it!=NULL;it=it->next){
        if(is_match(it->data,extra_args)) rList_push_back(result,it->data,elem_size);
    }
    return result;
}
