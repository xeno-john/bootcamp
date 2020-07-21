#include "p7.h"
#include <stdlib.h>
#include <stdio.h>

int* allocInLib()
{
    printf("\nAllocating integer with the use of a shared library.\n");
    int* value=(int*)malloc(sizeof(int));
    printf("\nGive a value to the integer: ");
    scanf("%d",value);
    return value;
}
void freeInLib( int* toBeFreed)
{
    printf("\nDeallocating integer with the use of a shared library.\n");
    free(toBeFreed);
    toBeFreed = NULL;
}
