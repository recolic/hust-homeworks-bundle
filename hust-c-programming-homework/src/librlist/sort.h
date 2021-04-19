#ifndef R_ALG_LIST_SORT_EXTENDC
#define R_ALG_LIST_SORT_EXTENDC

#include "list.h"

void rList_sort(struct rListDescriptor *desc,int (*cmpr)(void* a,void* b));

#endif
