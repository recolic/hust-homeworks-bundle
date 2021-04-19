#include "../cclib/containers.h"
#include <stdio.h>

typedef struct _test
{
    int a;
    double b;
} test;
int main()
{
    printf("%d\n", sizeof(test));
    HashTable *ht = iHashTable.Create(sizeof(test));
    test dat; dat.a=11;dat.b=6.6;
    iHashTable.Add(ht, "6666", 4, &dat);
    printf("----------\n");
    test *ret = iHashTable.GetElement(ht, "1234", 4); //buggy!
    printf("----------\n");
    if(ret == NULL)
        return 22;
    printf("----------\n");
    printf("ret>%d %lf", ret->a, ret->b);
    ret->a = 333; ret->b=3.333;
    printf("ret>%d %lf", ret->a, ret->b);

}

