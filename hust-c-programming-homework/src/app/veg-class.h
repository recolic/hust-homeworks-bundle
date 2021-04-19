#ifndef _PROJECT_VEG_CLASS_H
#define _PROJECT_VEG_CLASS_H 1
#include "common.h"
#include "data.h"
void veg_class_set(veg_class to_push);
void veg_class_ls(fd fout);
bool veg_class_rm(int code);

const veg_class *code_to_veg_class(int code);

#endif //_PROJECT_VEG_CLASS_H
