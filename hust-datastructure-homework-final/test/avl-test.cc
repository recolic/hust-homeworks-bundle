#include <rlib/stdio.hpp>
#include "../src/lib/avl.hpp"
using namespace rlib;
using namespace avl;

#include "AVL/AVL.h"
#include <rlib/functional.hpp>

#define N 10000000

void cavl_ins(AVL *&root) {
    for(int cter = 1; cter < N; ++cter) {
        root = Insert(root, cter);
    }
}
void cavl_del(AVL *&root) {
    for(int cter = 1; cter < N; ++cter) {
        root = Delete(root, cter);
    }
}
void cavl_ver(AVL *root) {
    for(int cter = 1; cter < N; ++cter) {
        if(!Exist(root, cter))
            printfln("Warn: {} not exist.", cter);
    }
}


void myavl_ins(tree<int> &tr)
{
    for (int cter = 1; cter < N; ++cter)
    {
        //printfln("cter is {}.", cter);
        tr.insert(-cter);
        //tr.dump();
    }
}
void myavl_del(tree<int> &tr)
{
    for (int cter = 1; cter < N; ++cter)
    {
        tr.erase(tr.find(-cter));
    }
}

void myavl_ver(tree<int> &tr) {
    for(int cter = 1; cter < N; ++cter) {
        if(!tr.exist(cter))
            printfln("Warn: {} not exist.", cter);
    }
}
void _naive_test(tree<int> &tr){
    for(int cter = 1; cter <= 10; ++cter) {
        println("round", cter);
        tr.insert(cter);
        tr.dump();
    }
    println("begin: ");tr.dump();
    for(int cter = 1; cter <= 10; ++cter) {
        println("round", cter);
        tr.erase(tr.find(cter));
        tr.dump();
    }

}


void naive_test(tree<int> &tr){
    for(int cter = 1; cter <= 10; ++cter) {
        println("round", -cter);
        tr.insert(-cter);
        tr.dump();
    }
    println("begin: ");tr.dump();
    for(int cter = 1; cter <= 10; ++cter) {
        println("round", -cter);
        tr.erase(tr.find(-cter));
        tr.dump();
    }

}
#include <random>
#include <algorithm>
void rand_ins(tree<int> &tr) {
    std::mt19937 randGen(1234);
    for(int cter = 1; cter <= 16; ++cter) {
        int toInsert = randGen();
        println("Inserting", toInsert);
        tr.insert(toInsert);
        tr.dump();
    }
}

int main() {
    tree<int> tr;
//    naive_test(tr);
//    rand_ins(tr);
//    tr.insert(5);
//    tr.insert(3);
//    tr.insert(6);
//    tr.insert(1);
//    tr.insert(7);
//    tr.insert(58);
//    tr.insert(38);
//    tr.insert(68);
//    tr.insert(18);
//    tr.insert(78);
//     tr.insert(21);
//    tr.insert(9);
//    tr.insert(4);
//    tr.insert(2);
//    tr.dump();
//    std::for_each(tr.cbegin(), tr.cend(), [](const int &i){print(i, "");});
//    println();
//    exit(0);
    AVL *root = NULL;

    printfln("Doing {} insert and {} delete", N, N);

    auto begin = std::chrono::high_resolution_clock::now();
    cavl_ins(root);
    auto end = std::chrono::high_resolution_clock::now();
    println(::std::chrono::duration<double>(end - begin).count());

    begin = end;
    cavl_del(root);
    end = std::chrono::high_resolution_clock::now();
    println(::std::chrono::duration<double>(end - begin).count());

    begin = end;
    myavl_ins(tr);
    end = std::chrono::high_resolution_clock::now();
    println(::std::chrono::duration<double>(end - begin).count());

    begin = end;
    myavl_del(tr);
    end = std::chrono::high_resolution_clock::now();
    println(::std::chrono::duration<double>(end - begin).count());

    return 0;
}
