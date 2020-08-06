#include "p9.h"
#include <stdlib.h>

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int                      i = 0; 
    int              *value = NULL;

    value = (int*)malloc(sizeof(int)); 
    
    if (NULL == value)
    {
        fprintf(stderr,"Error when allocating memory.\n");
    }
    else
    {

        for(i = 0; i < NUM_THREADS; ++i)
        {
            if(pthread_create(&threads[i], NULL, task, (void*)value))
            {
                DBG_PRINT(1,"Error: can't create thread. %d\n",pthread_create(&threads[i], NULL, task, (void*)value));
                break;
            }
        }

        // for(i = 0; i < NUM_THREADS; ++i)
        // {
        //     pthread_join(threads[i],NULL);
        // }

        free(value);
        value = NULL;
    }

    return 0;
}
