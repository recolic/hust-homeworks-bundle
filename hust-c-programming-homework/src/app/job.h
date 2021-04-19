#ifndef _CHW_JOB_H
#define _CHW_JOB_H 1
#include "common.h"
#include "data.h"
void job_set(job_info to_push);
void job_ls(fd fout);
bool job_rm(int no);

#endif //_CHW_JOB_H
