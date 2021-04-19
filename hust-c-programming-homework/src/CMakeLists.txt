cmake_minimum_required(VERSION 3.5) #Boost::system syntax support
project(chw)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0.0")
        message(FATAL_ERROR "Insufficient gcc version")
    endif()
else()
    message(FATAL_ERROR "gcc is required")
endif()

# This is to satisfy silly CLion syntax checker.
add_definitions(-D_ENABLE_CXX1X_AUTO_FIX)
set(CMAKE_CXX_FLAGS_DEBUG "-g -DMALLOC_CHECK_=2 -D__DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(SOURCE_MOD mod/console.c mod/filter.c mod/hash.c mod/fstr.c)
set(SOURCE_APP_CUI app/cmd.c app/main.c app/veg-class.c app/veg.c app/job.c app/shit-op.c)
set(SOURCE_APP_GUI app/cmd.c app/gui-main.c app/veg-class.c app/veg.c app/job.c app/shit-op.c)

# do check.sh
execute_process(COMMAND ./check.sh OUTPUT_VARIABLE CHECK_SH_O)
message("${CHECK_SH_O}")
set(CHECK_OK)
string(FIND "${CHECK_SH_O}" "fatal" CHECK_OK)
if(NOT "${CHECK_OK}" STREQUAL "-1")
    message(FATAL_ERROR "NEEDED dependency can't satisfy. Stopping configure...")
endif()

# compiler options
# set(SOURCE_FILES ${SOURCE_RLIST} ${SOURCE_MOD} ${SOURCE_APP})
set(CMAKE_C_STANDARD 11)
include_directories(.)
include_directories(./mod)
include_directories(./librlist)

add_subdirectory(librlist)

# cclib custom makefile configurations
# set the output destination
set(CCLIB_A cclib/libccl.a)
# create a custom target called build_scintilla that is part of ALL
# and will run each time you type make
add_custom_target(build_ccl ALL
        COMMAND make libccl.a
        WORKING_DIRECTORY cclib
        COMMENT "Calling cclib makefile to build libccl.a")
# now create an imported static target
add_library(libccl STATIC IMPORTED)
# Import target "scintilla" for configuration ""
set_property(TARGET libccl APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libccl PROPERTIES
        IMPORTED_LOCATION_NOCONFIG "${CCLIB_A}")
# now you can use scintilla as if it were a regular cmake built target in your project
add_dependencies(libccl build_ccl)

# setup cli
add_executable(chw-cli ${SOURCE_MOD} ${SOURCE_APP_CUI})
target_link_libraries(chw-cli libccl rlistlib)
add_custom_command(TARGET chw-cli POST_BUILD COMMAND mv chw-cli ../bin/ COMMENT "Moving exec to bin...")
add_custom_command(TARGET chw-cli POST_BUILD COMMAND rm -rf ../bin/gui)
add_custom_command(TARGET chw-cli POST_BUILD COMMAND cp -r web/client/min ../bin/gui COMMENT "Moving gui to bin...")
add_custom_command(TARGET chw-cli POST_BUILD COMMAND cp *.sh ../bin/ COMMENT "Moving scripts to bin...")
add_custom_command(TARGET chw-cli POST_BUILD COMMAND rm ../bin/cmake_clean.sh COMMENT "Do cleanup...")


# build wserver
add_subdirectory(web/server)

# deleted # # frontend will be impl seperately.
# deleted # # import gtk3
# deleted # find_package(PkgConfig REQUIRED)
# deleted # pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# deleted # include_directories(${GTK3_INCLUDE_DIRS})
# deleted # link_directories(${GTK3_LIBRARY_DIRS})
# deleted # add_definitions(${GTK3_CFLAGS_OTHER})
# deleted # 
# deleted # # setup gui
# deleted # add_executable(chw-gui ${SOURCE_MOD} ${SOURCE_APP_GUI})
# deleted # target_link_libraries(chw-gui libccl rlistlib ${GTK3_LIBRARIES})
