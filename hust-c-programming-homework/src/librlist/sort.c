#include "sort.h"
#include <stdlib.h>

void rList_sort(struct rListDescriptor *desc,int (*cmpr)(void* a,void* b)){
    rListIterator infolist=desc->first;
    if(desc->first == NULL) return;
    int FLAG_SORTED=0;
    while(!FLAG_SORTED){
        FLAG_SORTED=1;
        struct rListNode* iterator=infolist->next,*previtem=infolist;
        while(iterator!=NULL){
            if(cmpr(previtem->data,iterator->data)){
                rList_swapElem(desc,iterator,previtem,1);
                infolist=desc->first;
                FLAG_SORTED=0;
                break;
            }
            iterator=iterator->next;
            previtem=previtem->next;
        }
    }
}
