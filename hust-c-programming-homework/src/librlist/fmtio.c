#include "fmtio.h"
#include <unistd.h>

int fmt_read_file(fd fin, rList dataBuf, size_t sizeofObj, const void *delimiter)
// Pass nullptr as delimiter to use 0 bytes as delimiter. //Return read obj counter, neg if error.
{
    bool mustFree = delimiter == nullptr;
    if(mustFree)
        delimiter = calloc(1, sizeofObj);
    int counter = 0;
    while(true)
    {
        void *mem = malloc(sizeofObj);
        auto bytes = read(fin, mem, sizeofObj);
        if(bytes == -1) die("read fin error. current counter=%d", counter);
        if(bytes < sizeofObj) break;
        if(0 == memcmp(mem, delimiter, sizeofObj)) break;
        rList_push_back(dataBuf, mem, sizeofObj);
        ++counter;
        free(mem);
    }
    if(mustFree)
        free((void *)delimiter);
    return counter;
}

int fmt_write_file(fd fout, rList dataBuf, size_t sizeofObj, const void *delimiter)
// Pass nullptr as delimiter to use 0 bytes as delimiter. //Return read obj counter, neg if error.
{
    bool mustFree = delimiter == nullptr;
    if(mustFree)
        delimiter = calloc(1, sizeofObj);
    int counter = 0;
    for(rListIterator it = dataBuf->first; it != nullptr; it = it->next)
    {
        auto ret = write(fout, it->data, sizeofObj);
        if(ret < sizeofObj) die("write fout error: write() return %d, current counter=%d", ret, counter);
        ++counter;
    }
    auto ret = write(fout, delimiter, sizeofObj);
    if(ret != sizeofObj)
        die("write delimiter failed. write()=%d, counter=%d", ret, counter);
    if(mustFree)
        free((void *)delimiter);
    return counter;
}
