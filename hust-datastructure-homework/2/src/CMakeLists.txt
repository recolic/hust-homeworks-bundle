cmake_minimum_required(VERSION 3.5)
project(hust__)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -DMALLOC_CHECK_=2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")

include_directories("/usr/include")
include_directories("/usr/local/include")
include_directories(".")

set(BUILD_SRC main.cc reflected_impl.hpp lab_list.hpp labafx.hpp general_ui.hpp parser.hpp)
add_executable(exp2 ${BUILD_SRC})

