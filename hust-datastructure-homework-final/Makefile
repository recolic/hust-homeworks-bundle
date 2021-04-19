.PHONY: bin test clean all

all: bin test

bin:
	[ -d build ] || mkdir build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release ../src && make && cp hust-ds* ../bin && cd -

bin-debug:
	[ -d build ] || mkdir build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug ../src && make && cp hust-ds* ../bin && cd -

bin-win:
	[ -d build ] || mkdir build
	cd build && cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ../src && make && cp hust-ds* ../bin && cd -

bin-win-debug:
	[ -d build ] || mkdir build
	cd build && cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Debug ../src && make && cp hust-ds* ../bin && cd -

test: test-avl test-set test-set2

test-debug: test-avl-debug test-set-debug

test-avl:
	cd test && g++ avl-test.cc AVL/AVL.cpp -lr -I../src/lib -O3 -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/avl-test && cd -

test-avl-debug:
	cd test && g++ avl-test.cc AVL/AVL.cpp -lr -I../src/lib -g -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/avl-test && cd -

test-set:
	cd test && g++ set-test.cc -lr -I../src/lib -O3 -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/set-test && cd -

test-set-debug:
	cd test && g++ set-test.cc -lr -I../src/lib -g -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/set-test && cd -

test-set2:
	cd test && g++ 2set-test.cc -lr -I../src/lib -O3 -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/2set-test && cd -

test-set2-debug:
	cd test && g++ 2set-test.cc -lr -I../src/lib -g -DENABLE_RAVL_DEBUG_DUMP -DENABLE_RAVL_FOREACH_NODE -o ../bin/2set-test && cd -

clean:
	rm -f bin/hust-ds bin/avl-test test/avl-test
	cd src && ./cmake_clean.sh
	rm -rf build
