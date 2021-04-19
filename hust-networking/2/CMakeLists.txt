cmake_minimum_required(VERSION 3.5)
project(stop_wait)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(WARNING "!!!!! CMAKE IS DEPRECATED !!! DO NOT USE IT !!!!!")

######################################################
# Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git" OR EXISTS "${CMAKE_SOURCE_DIR}/../.git")
  set(default_build_type "Debug")
endif()


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
######################################################

set(Boost_USE_STATIC_LIBS ON)
find_package(Threads REQUIRED)
#find_package(Boost REQUIRED system)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

include(lib/rlib/cmake/cmake.include)
find_package(rlib)
if(NOT rlib_FOUND)
    include_directories(lib)
    add_subdirectory(lib/rlib/cmake)
endif()

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/include INC_LIST)
add_executable(stop_wait ${SRC_LIST} ${INC_LIST})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")
find_library(NETSIM_LIB libnetsim.a ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(stop_wait ${NETSIM_LIB} r)

