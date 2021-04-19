#!/bin/bash
make clean
cd librlist
./.clean.ccmake.sh
cd -
rm -rf wserver cmake-build-debug/ cmake_install.cmake Makefile CMakeFiles CMakeCache.txt
rm cclib/*.o

cd ./web/server/
./cmake_clean.sh
cd -
