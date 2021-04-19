# notes

### confirm sizeof(unsigned char)==1 
Required by hash.cc, l22, assert(size%sizeof(uchar)==0)

### required: C11, UnixSysCall.
Tested under: gcc 7.1.1, c11, Linux 4.11.6-3-ARCH, fish 2.5.0, cmake 3.8.2, gnu-bash 4.4.12(1)

### linux+bash
Required by console.cc

DO not optimize 'pass by value' in ..._set function, which's error-prone in c without reference.

### Rely compo:
mkdir bash 

//TODO: assert: dprintf is success (dangerous op.)

### lib bug to report:
libccl/hashtable.c line275: v != NULL while ele not exist.

Segment fault while trying to visit it. no further test.

case in tests/test-ht.c