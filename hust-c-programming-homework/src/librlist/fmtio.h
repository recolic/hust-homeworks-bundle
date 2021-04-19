#ifndef _CHW_FMTIO_H_H
#define _CHW_FMTIO_H_H 1

#include "common.h"
#include "list.h"

int fmt_read_file(fd fin, rList dataBuf, size_t sizeofObj, const void *delimiter);
// Pass nullptr as delimiter to use 0 bytes as delimiter. //Return read obj counter, neg if error.

int fmt_write_file(fd fout, rList dataBuf, size_t sizeofObj, const void *delimiter);
// Pass nullptr as delimiter to use 0 bytes as delimiter. //Return read obj counter, neg if error.

#endif //_CHW_FMTIO_H_H
