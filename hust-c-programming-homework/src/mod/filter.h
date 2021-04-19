#ifndef _SRC_FILTER_H
#define _SRC_FILTER_H 1

#include "../common.h"

typedef enum {VEG_CLASS_CODE, VEG_NAME, VEG_NEU, VEG_CLASS_CODE_BY_INFO, VEG_NAME_BY_JOB, JOB_YEAR} FILTER_CLASS;
void filter(fd fin, fd fout, bool fullMatch, const char *keyString, FILTER_CLASS type);

void printFd(fd fin);
//print as string.

#endif //_SRC_FILTER_H
