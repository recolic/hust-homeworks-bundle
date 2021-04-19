cmake_minimum_required(VERSION 3.2)
project(hust__)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -DMALLOC_CHECK_=2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories("/usr/include")
include_directories("/usr/local/include")
include_directories(".")

### create a custom target called build_libr that is part of ALL
### and will run each time you type make
##add_custom_target(build_libr ALL
##        COMMAND make
##        WORKING_DIRECTORY rlib
##        COMMENT "Calling rlib makefile to build libr.a")
add_library(r STATIC rlib/libr.cc)

set(BUILD_SRC main.cc reflected_impl.hpp btree.hpp general_ui.hpp parser.hpp)
add_executable(exp3 ${BUILD_SRC})
##add_dependencies(exp3 build_libr)

target_link_libraries(exp3 r)