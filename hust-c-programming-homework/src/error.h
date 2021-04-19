#ifndef _SRC_ERROR_H
#define _SRC_ERROR_H 1
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define ___unpack_arg_2(arg) arg
#define _do_except(msg, ...) do{ \
                            printf("Exception at %s:%d | errno=%d:%s >", __FILE__, __LINE__, errno, strerror(errno)); \
                            printf(msg, ##__VA_ARGS__); \
                            printf("\n\n"); \
                            quick_exit(errno?errno:126); \
                        }while(0)
#define except(msg, ...) _do_except(msg, ##__VA_ARGS__)
#define die except
 
 #ifdef __DEBUG
 #define RECORD printf("R> %s:line%d\n", __FILE__, __LINE__);
 #define debug_if(sth) if(sth)
 #else
 #define RECORD
 #define debug_if(sth) if(false)
 #endif
 #define debug debug_if(true)
 


#endif
