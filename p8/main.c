#include "p8.h"
#include <stdlib.h>

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int                      i = 0; 

    for(i = 0; i < NUM_THREADS; ++i)
    {

        if(pthread_create(&threads[i], NULL, task, (void*)(long)i))
        {
            DBG_PRINT(1,"Error: can't create thread. %d\n",pthread_create(&threads[i], NULL, task, (void*)(long)i));
        }

    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i],NULL);
    }

    return 0;
}
