#include <stdio.h>
#include <dlfcn.h>
#include<stdlib.h>

/*
 * used the following sources:
 * https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/dlsym.htm
 * https://docs.oracle.com/cd/E88353_01/html/E37843/dlsym-3c.html
 * https://stackoverflow.com/questions/1354537/dlsym-dlopen-with-runtime-arguments
 */

int main(void)
{
    void *handle = dlopen("/home/uic84214/bootcamp/p7/libsample.so", RTLD_LOCAL | RTLD_LAZY);
    int                                                         *(*allocate_in_lib)() = NULL;
    void                                                  (*deallocate_in_lib)(int *) = NULL;
    int                                                              *to_be_allocated = NULL;

    if (NULL != handle)
    {
        allocate_in_lib = (int*(*)())dlsym(handle, "alloc_in_lib");
        deallocate_in_lib = (void (*)(int *))dlsym(handle, "free_in_lib");

        if ((NULL != allocate_in_lib) && (NULL != deallocate_in_lib))
        {
            to_be_allocated = allocate_in_lib();
            printf("%d ",*to_be_allocated);
            deallocate_in_lib(to_be_allocated);
        }
        else
        {
            fprintf(stderr,"Error when creating connections between function pointers and actual functions in libsample.so.\n");
        }
        
    }
    else
    {
        fprintf(stderr,"Error. Bad address for the library.\n");
    }

    if (0 != dlclose(handle))
    {  
        fprintf(stderr,"Failed to close the handle.\n");
    }

 /* free(allocate_in_lib);
  * free(deallocate_in_lib);
  * free(to_be_allocated);
  */ /* gives segmentation fault for some reason */
    to_be_allocated = NULL;
    
    return 0;
}