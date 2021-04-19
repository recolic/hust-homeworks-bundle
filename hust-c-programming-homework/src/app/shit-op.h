#ifndef _CHW_SHIT_OP_H
#define _CHW_SHIT_OP_H 1

#include "common.h"

void _impl_job_report_by_veg_class(fd fout); //#print className+sumArea+sumWeight
void _impl_job_report_by_year_and_veg_name_decrease(fd fout, int year_begin, int year_end/*Not included*/); //#print vegName+className+sumArea+sumWeight(decrease)
void _impl_check_weight_by_veg_class(fd fout, int classNum); //#print sumWeight

#endif //_CHW_SHIT_OP_H
