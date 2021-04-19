#ifndef _SRC_COMMON_DECL_H
#define _SRC_COMMON_DECL_H 1
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "error.h"

#define ___unpack_arg(arg) arg

#define decltype(type_t) typeof(___unpack_arg(type_t))
#ifdef _ENABLE_CXX1X_AUTO_FIX
#define auto __auto_type
#endif

#define nullptr NULL

#define ___new(data_type) (data_type *)malloc(sizeof(data_type))
#define new(data_type) ___new(___unpack_arg(data_type))

#define ___min(a, b) ((a) < (b) ? (a) : (b))
#define min(a, b) ___min(___unpack_arg(a), ___unpack_arg(b))

typedef int fd;

#endif
