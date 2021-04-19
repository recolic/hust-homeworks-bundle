#include "hash.h"
#include <string.h>
/*
    This is the popular `times 33' hash algorithm which is used by perl 
    and that also appears in Berkeley DB. This is one of the best known hash functions 
    for strings because it is both computed very fast and distributes very well.
    
    This hash function is adapted from Chris Torek's Hash function for text in C, 
    Usenet message < 27038@mimsy.umd.edu > in comp.lang.c , October, 1990." 
    in Rich Salz's USENIX 1992 paper about INN 
    with GLU license.
*/
unsigned long
___hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

unsigned long ulong_hash(const void *data, size_t size)
{
    unsigned char *strbuf = malloc(size + sizeof(unsigned char));
    memcpy(strbuf, data, size);
    strbuf[size%sizeof(unsigned char)] = 0;
    for(size_t cter = 0; cter < size % sizeof(unsigned char); ++cter)
    {
        if(!strbuf[cter]) strbuf[cter] = 73;
    }
    auto ret = ___hash(strbuf);
    free(strbuf);
    return ret;
}

int int_hash(const void *data, size_t size)
{
    return (int)ulong_hash(data, size);
}