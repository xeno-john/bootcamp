#include <stdlib.h>
#include "../DBG_PRINT.h"
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 *  @brief Function receives a void* and prints the int at that location.
 *  @param arg [in] the address at which the index that's going to be printed is 
 */
void *task(void *arg);

void *task(void *arg)
{
    pthread_mutex_lock(&mutex);
    DBG_PRINT(5,"Argument: %d\n",(*(int*)arg)++); 
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

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
<<<<<<< HEAD
                break;
=======
>>>>>>> e3a2681ded6e3fbc44dff1a56ff017b230468dda
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
