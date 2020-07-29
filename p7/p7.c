#include "p7.h"
#include <stdlib.h>
#include <stdio.h>

/**
 *  @brief Function that returns an allocated int pointer.
 *  @return int allocated_pointer - allocated *int that will be used in the caller function 
 */
int* alloc_in_lib()
{
    printf("\nAllocating integer with the use of a shared library.\n");
    int* allocated_pointer=(int*)malloc(sizeof(int));
    printf("\nGive a value to the integer: ");
    
    if (0 == scanf("%d",allocated_pointer))
    {
        fprintf(stderr,"Failure reading given value.\n");
        free(allocated_pointer);
        allocated_pointer = NULL;
    }
    
    return allocated_pointer;
}

/**
 *  @brief Function that receives data, serializes it, and returns the serialized size in bytes.
 *  @param [in] component_info - pointer to the struct that will be serialized
 *  @param [in] serialization_buffer - void ptr in which we will stock the data
 *  @param [in] buffer_size - size of the buffer
 *  @param [in] result - pointer which will have the value at that address 0 if everything went ok, -1 otherwise
 *  @return int serialization_size - will be -1 if something goes wrong, and the size in bytes of serialized data if everything goes accordingly
 */
void free_in_lib(int* toBeFreed)
{
    printf("\nDeallocating integer with the use of a shared library.\n");
    free(toBeFreed);
    toBeFreed = NULL;
}
