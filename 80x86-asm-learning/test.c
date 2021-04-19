#include <stdio.h>

extern int func(int i);
//int func(int i) {
//    __asm nop;
//    __asm nop;
//    return i*i;
//}

int main(){
    int i = 1;
    printf("i is %d\n", func(i));
    return 0;
}
