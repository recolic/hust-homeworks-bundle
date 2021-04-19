cmake_minimum_required(VERSION 2.8.5)
project(mxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_DEBUG "-g")

find_package(rlib)
if(NOT rlib_FOUND)
    # If you are not willing to install rlib...
    add_library(r STATIC ./lib/rlib/libr.cc)
    set(rlib_LIBRARIES r)
    include_directories(./lib)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(rlib_CXX_FLAGS "-Wno-terminate -Wno-reorder")
    endif()
    message(WARNING "rlib is not installed to your CMAKE_MODULE_PATH. I'll use the one packed into this project.")
endif()

include_directories(./src)
include_directories(./lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${rlib_CXX_FLAGS}")

add_executable(mxx1 src/ll.c src/ll.h src/mxx1.cc)
target_link_libraries(helm ${rlib_LIBRARIES})

if(STATIC_BUILD)
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
    set_target_properties(helm PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()


