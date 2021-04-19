#include "../console.h"

int main()
{
    doCmd(FD_DEFAULT, FD_DEFAULT, FD_DEFAULT, "echo 'Hello world!!!'");
    return 0;
}