### Compilation note

In CMakeLists.txt, you can uncomment the line 12 `# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOMPILE_NO_ERASE -DNODES_PRE_ALLOC_MEM=1000000")` to get much higher performance. That is, remove an O(n) factor from dfs/bfs algorithm. However, this will make function `DeleteVex(removeNode)` unavailable, because this will invalidate most node aliases/addresses.

You can use at most `NODES_PRE_ALLOC_MEM` nodes in your test case. By default, that's 1M, which eats you about 333MBytes memory. You can set it to 10M to test my algorithm further, which needs about 3.3GB memory. Don't forget `-DCMAKE_BUILD_TYPE=Release`, which gives `-O3` to let your test boost 4 times!

I provide pre-compiled binary in both version, for both linux and windows.

### My tests

- normal version

|nodes|time|memory|
|:---:|:---:|:---:|
|1K|0.15s|tiny|
|10K|27s|tiny|

- high performance version

|nodes|time|memory|
|:---:|:---:|:---:|
|1K|0.04s|tiny|
|10K|0.40s|tiny|
|100K|4.3s|55MB|
|1M|44s|600MB|
|10M|570s|6GB|
