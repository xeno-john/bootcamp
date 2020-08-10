#include "../DBG_PRINT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

int condition_met                                 = 0;
pthread_cond_t       cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;


/**
 *  @brief Function that receives an int through a void pointer (thread_id) and keeps the thread running as long as the given condition is met.
 *  @param arg [in] void ptr to an integer (casted to long to be the exact same size as void*)
 */
void *task(void *arg);

void *task(void *arg)
{
    int rc = 0;
    printf("%d",rc);
    rc = pthread_mutex_lock(&mutex);

    long tid = (long)arg;

    while (0 == condition_met)
    {
        DBG_PRINT(5,"Thread %li doing stuff.\n",tid);
        rc = pthread_cond_wait(&cond,&mutex);
    }    

    rc = pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


int main(void)
{
    pthread_t threads[NUM_THREADS];
    int i = 0; 
    int rc = 0;
    printf("%d",rc); /* avoiding the pathetic error of "variable set but not used */

    for (i = 0; i < NUM_THREADS; ++i)
    {

        if (0 != pthread_create(&threads[i], NULL, task, (void*)(long)i))
        {
            DBG_PRINT(1,"Error: can't create thread. %d\n",pthread_create(&threads[i], NULL, task, (void*)(long)i));
            exit(EXIT_FAILURE);
        }

    }

    sleep(5);  /* Sleep is not a very robust way to serialize threads */
    rc = pthread_mutex_lock(&mutex);
    /* The condition has occured. Set the flag and wake up any waiting threads */
    condition_met = 1;
    printf("Wake up all waiting threads...\n");
    rc = pthread_cond_broadcast(&cond);

    rc = pthread_mutex_unlock(&mutex);

    printf("Wait for threads and cleanup\n");

    for (i=0; i<NUM_THREADS; ++i) 
    {
        rc = pthread_join(threads[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    printf("Main completed\n");
    return 0;
}