#include "p7.h"
#include <stdio.h>

int main(void)
{
    int *to_be_allocated = alloc_in_lib();

    if (NULL != to_be_allocated)
    {
        printf("%d ",*to_be_allocated);
        free_in_lib(to_be_allocated);
    }
    else
    {
        fprintf(stderr,"Failed to instantiate function pointer.\n");
    }
    
    return 0;
}