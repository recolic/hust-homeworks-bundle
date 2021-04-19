Recolic Note:

I only modified Makefile and csim.cc. Just copy them into your cachelab-handout and run `make`.

I used my self-written C++ util library `rlib`. EVERY code line (except `rlib/3rdparty/*`) in rlib
 was written by my hand, so I'm using rlib in my EVERY C++ experiments/homeworks.

You need a C++17 compiler to compile my code.

this project is using rlib commit 9a0eaea923fcb60dcc6bac41d5be9ea12d7223cd

```
This is the handout directory for the CS:APP Cache Lab. 

************************
Running the autograders:
************************

Before running the autograders, compile your code:
    linux> make

Check the correctness of your simulator:
    linux> ./test-csim

Check the correctness and performance of your transpose functions:
    linux> ./test-trans -M 32 -N 32
    linux> ./test-trans -M 64 -N 64
    linux> ./test-trans -M 61 -N 67

Check everything at once (this is the program that your instructor runs):
    linux> ./driver.py    

******
Files:
******

# You will modifying and handing in these two files
csim.c       Your cache simulator
trans.c      Your transpose function

# Tools for evaluating your simulator and transpose function
Makefile     Builds the simulator and tools
README       This file
driver.py*   The driver program, runs test-csim and test-trans
cachelab.c   Required helper functions
cachelab.h   Required header file
csim-ref*    The executable reference cache simulator
test-csim*   Tests your cache simulator
test-trans.c Tests your transpose function
tracegen.c   Helper program used by test-trans
traces/      Trace files used by test-csim.c
```
