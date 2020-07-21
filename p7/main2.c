#include <stdio.h>
#include <dlfcn.h>
#include<stdlib.h>



// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/dlsym.htm
// https://docs.oracle.com/cd/E88353_01/html/E37843/dlsym-3c.html
// https://stackoverflow.com/questions/1354537/dlsym-dlopen-with-runtime-arguments


int main(void)
{
    // this is a pointer that contains the location of the library
    // and some flags 
    void *handle = dlopen("/home/uic84214/bootcamp/p7/libsample.so", RTLD_LOCAL | RTLD_LAZY);

    // using dlsym and the precedent 'handle'
    // we set the address of the function pointers
    // to the ones found in the given library
    // in this manner, we can use the functions 
    // through the pointers.
    // dlsym retuns void function pointer
    // so it needs to be cast to whatever the type of wanted
    // function is.
    // (that was a pain)
    int* (*allocateInLib)() = (int*(*)())dlsym(handle, "allocInLib");;
    void (*deallocateInLib)(int *) = (void (*)(int *))dlsym(handle, "freeInLib");;
    int *toBeAllocated ;

    // int returnCode;

    // if the given path is wrong 'handle' will be NULL.
    // we treat that case here:
    if(handle == NULL)
    {
        fprintf(stderr,"Library not found.");
        exit(EXIT_FAILURE);
    }

    /* open the needed object */

    /* find the address of function and data objects */

    // test scenarios to see if the functions we're searching for
    // in the given library 
    // actually exist
    if(allocateInLib == NULL)
    {
        fprintf(stderr,"alloInLib not found.");
        exit(EXIT_FAILURE);
    }
    if(deallocateInLib == NULL)
    {
        fprintf(stderr,"deallocInLib not found.");
        exit(EXIT_FAILURE);
    }
    
    // the pointer to the function found in the given library
    // can be used 
    // as a normal function
    toBeAllocated = allocateInLib();

    // testing whether everything went OK 
    // by printing the value allocated in the
    // allocInLib function
    // called through the allocateInLib pointer
    printf("%d ",*toBeAllocated);

    deallocateInLib(toBeAllocated);

    // somehow dlclose doesn't close the handle and gives error code.

    // returnCode = dlclose(handle);
    // if(returnCode 0= 0 )
    // {
    //     fprintf(stderr,"Failed to close the handler for the library.\n");
    //     exit(EXIT_FAILURE);
    // }
    return 0;
}