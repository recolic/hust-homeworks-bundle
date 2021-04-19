#ifndef _CHW_VEG_H
#define _CHW_VEG_H 1
#include "common.h"
#include "data.h"
void veg_info_set(veg_info to_push);
void veg_info_ls(fd fout);
bool veg_info_rm(const char *name);

const veg_info *no_to_veg_info(int no);

#endif //_CHW_VEG_H
