#include "common.h"
#include "cmd.h"
#include <stdio.h>

void veg_class_constructor();
void veg_info_constructor();
void job_constructor();

int main(int arglen, char **argv)
{
    if(sizeof(unsigned char) != 1) die("assertion failed: sizeof uchar != 1");
    system("mkdir /tmp/.chw > /dev/null 2>&1");
    veg_class_constructor(); veg_info_constructor(); job_constructor();
    return do_cmd_process(arglen, argv);
}
