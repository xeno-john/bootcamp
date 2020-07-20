#include "p8.h"
#include <stdlib.h>

int main(void)
{
    // here we declare an array of (p)threads
    pthread_t threads[NUM_THREADS];
    int i = 0; // contor value

    for(i = 0; i < NUM_THREADS; ++i)
    {
        // pthread_create() function starts a new thread in 
        // the calling process
        if(pthread_create(&threads[i], NULL, task, (void*)(long)i))
        {
            DBG_PRINT(1,"Error: can't create thread. %d\n",pthread_create(&threads[i], NULL, task, (void*)(long)i));
            exit(EXIT_FAILURE);
        }
    }

    // pthread_join() function waits for the speecified 
    // by thread to terminate.
    // if that thread has already terminated
    // pthread_join() returns immediately.
    // - Linux Programmer's Manual (man)
    for(i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i],NULL);
    }
    return 0;
}
