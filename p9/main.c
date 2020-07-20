#include "p9.h"
#include <stdlib.h>

int main(void)
{
    // here we declare an array of (p)threads
    pthread_t threads[NUM_THREADS];
    int i = 0; // contor value

    int *value = 0; // the value that will be passed to the function in the threads
    value = (int*)malloc(sizeof(int)); // allocating memory for the pointer
    
    if(value == NULL) // verify if the allocation was succesfull
    {
        fprintf(stderr,"Error when allocating memory.\n");
        exit(EXIT_FAILURE); // if not, terminate the exectuion
    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        // pthread_create() function starts a new thread in 
        // the calling process
        if(pthread_create(&threads[i], NULL, task, (void*)value))
        {
            DBG_PRINT(1,"Error: can't create thread. %d\n",pthread_create(&threads[i], NULL, task, (void*)value));
            exit(EXIT_FAILURE);
        }
    }

    /* pthread_join() function waits for the speecified 
     by thread to terminate.
     if that thread has already terminated
     pthread_join() returns immediately.
     - Linux Programmer's Manual (man)
    */
    for(i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i],NULL);
    }

    // deallocating the memory used for the value pointer.
    free(value);
    value = NULL;

    return 0;
}
