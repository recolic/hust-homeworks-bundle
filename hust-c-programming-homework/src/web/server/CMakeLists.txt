cmake_minimum_required(VERSION 3.5) #Boost::system syntax support
project(chw-wserver)

set(CMAKE_CXX_STANDARD 14)
include_directories(libwebsocket++)
include_directories(.) # rlib

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED system)
find_package(Threads REQUIRED)

set(SOURCE_FS main.cc mod/console.cc)

add_executable(wserver ${SOURCE_FS})
target_link_libraries(wserver Boost::system)
target_link_libraries (wserver ${CMAKE_THREAD_LIBS_INIT})
add_custom_command(TARGET wserver POST_BUILD COMMAND mv wserver ../../../bin/wserver COMMENT "Move wserver to top dir...")
