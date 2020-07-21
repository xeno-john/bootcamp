#include "p7.h"
#include <stdio.h>

int main(void)
{
    int *toBeAllocated = allocInLib();
    printf("%d ",*toBeAllocated);
    freeInLib(toBeAllocated);
    return 0;
}