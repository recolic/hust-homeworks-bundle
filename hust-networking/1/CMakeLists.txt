cmake_minimum_required(VERSION 3.2)
project(netw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set(Boost_USE_STATIC_LIBS ON)
find_package(Threads REQUIRED)
#find_package(Boost REQUIRED system)

include_directories(${Boost_INCLUDE_DIRS} .)

if(MSYS OR MINGW)
    set(DISABLE_FS TRUE)
    add_definitions(-DUSE_MINGW_FS_FIX)
# My Mingw-w64 is providing thread lib, so disabling this...
#    add_definitions(-DRLIB_SWITCH_USE_MINGW_THREAD_FIX)
#    include_directories(./lib/mingw-thread-fix)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-noreturn")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
endif()


include(lib/rlib/cmake/cmake.include)
find_package(rlib)
if(NOT rlib_FOUND)
    include_directories(lib)
    add_subdirectory(lib/rlib/cmake)
endif()

set(SRC_SRC src/server.hpp src/messages.hpp src/http.hpp src/listener.hpp src/handler.hpp src/listener.cc src/main.cc src/handler.cc src/req_processor.hpp src/config.hpp src/log.hpp)
set(SRC_LIB lib/thread_pool.hpp lib/unordered_map_patch.hpp lib/dump_file.hpp lib/conf_parser.hpp)
add_executable(netw ${SRC_SRC} ${SRC_LIB})

target_link_libraries(netw Threads::Threads)
#target_link_libraries(netw Boost::system)
if(NOT DISABLE_FS)
    target_link_libraries(netw stdc++fs)
endif()
# Need not link rlib if using cxx17
target_link_libraries(netw r)
if(WIN32)
    target_link_libraries(netw ws2_32)
endif()

add_executable(test-thread-pool lib/thread_pool.hpp test/thread_pool.cc)
target_link_libraries(test-thread-pool Threads::Threads)
target_link_libraries(test-thread-pool r)

