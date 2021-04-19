/*
 * Unused.
 */

/*
#ifndef _CHW_FMTIO_H
#define _CHW_FMTIO_H 1

#include "common.h"

#ifdef __cplusplus
#error Fatal: You should NEVER use fmtio.h to operate C++ class. Please DELETE this module before compiling as C++!
#endif

size_t fmt_read_object_arr(fd fin, void *pObjArrayBuf, size_t sizeofObj, size_t maxObjToRead, const void *delimiter);
// Pass nullptr as delimiter to use 0 bytes as delimiter.

size_t fmt_write_object_arr(fd fout, const void *pObjArrayBuf, size_t sizeofObj, size_t maxObjToWrite, const void *delimiter);
// Pass nullptr as delimiter to use 0 bytes as delimiter.

#endif //_CHW_FMTIO_H
*/