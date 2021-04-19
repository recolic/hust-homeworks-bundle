#ifndef R_ALG_SEARCH_ITERATION_EXTENDC
#define R_ALG_SEARCH_ITERATION_EXTENDC

#include "list.h"

rListIterator rList_search(rListDescriptor* desc,int (*is_match)(void* item,void* extra_args),void* extra_args);
rListDescriptor* rList_multisearch(rListDescriptor* desc,int (*is_match)(void* item,void* extra_args),void* extra_args,int elem_size);

#endif
