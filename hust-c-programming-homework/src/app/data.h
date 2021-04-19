#ifndef _SRC_DATA_H
#define _SRC_DATA_H 1

#include "common.h"

#define DATA_DUMP_PATH_HEAD "/tmp/.chw/dat-"
#define MAX_OBJECT 1024

typedef struct _veg_class {
    int code;
    char name[64];
} veg_class;

typedef struct _veg_info {
    int no; //Must self-inc autoly.
    char name[64];
    const veg_class *pclass;
    int ___class_code; //Unused(!!Unmaintained!!). Just to make the silly doc happy. //Defined as pclass->code
    char nutr_info[64];
} veg_info;

typedef struct _job_info {
    int no;
    const veg_info *pveg;
    int ___veg_no; //Unused(!!Unmaintained!!). Just to make the silly doc happy. //Defined as pveg->no
    int area;
    float weight;
    int year;
    char ___year[5]; //Unused(!!Unmaintained!!). Just to make the silly doc happy. //Defined as string(year)
} job_info;

#endif