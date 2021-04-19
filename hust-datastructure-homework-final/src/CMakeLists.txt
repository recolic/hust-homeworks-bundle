cmake_minimum_required(VERSION 3.2)
project(hust-ds)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -DMALLOC_CHECK_=2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# For codegen.py
add_definitions("-D__refl_func__=")
add_definitions("-D__refl_class__=")
add_definitions("-DENABLE_INSERT_NULL_CHECK")
add_definitions("-DENABLE_RAVL_DEBUG_DUMP")
add_definitions("-DENABLE_RAVL_FOREACH_NODE")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("/usr/include")
include_directories("/usr/local/include")
include_directories("/usr/include/c++/7.3.0") # Fix clion bug

include_directories(".")
include_directories("./lib")
include_directories("./lib/json/single_include")
include_directories("./lib/gc")
include_directories("./lib/cpp-readline/src")

add_library(r STATIC lib/rlib/libr.cc)

set(SOURCE_SRC main.cc reflected_impl.hpp general_ui.hpp parser.hpp person.hpp db.hpp)
set(LIB_SRC lib/avl.hpp lib/set.hpp)
set(BUILD_SRC ${LIB_SRC} ${SOURCE_SRC})

add_executable(hust-ds-no-menu ${BUILD_SRC})
add_executable(hust-ds ${BUILD_SRC})
target_compile_definitions(hust-ds PRIVATE ENABLE_SILLY_FAKE_MENU=)
IF (WIN32)
	set_target_properties(hust-ds PROPERTIES LINK_FLAGS "-static" )
	set_target_properties(hust-ds-no-menu PROPERTIES LINK_FLAGS "-static" )
ENDIF ()

target_link_libraries(hust-ds r)
target_link_libraries(hust-ds-no-menu r)
target_link_libraries(hust-ds Threads::Threads)
target_link_libraries(hust-ds-no-menu Threads::Threads)
