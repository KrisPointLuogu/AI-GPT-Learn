#include <stdio.h>
#include "arginit.h"

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    arg_init(argc, argv);
    return 0;
}
