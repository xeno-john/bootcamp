#include "p10.h"
#include <unistd.h>

int conditionMet = 0;
pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;


int main(void)
{
    // here we declare an array of (p)threads
    pthread_t threads[NUM_THREADS];
    int i = 0; // contor value
    int rc = 0;
    printf("%d",rc);

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
    sleep(5);  /* Sleep is not a very robust way to serialize threads */
    rc = pthread_mutex_lock(&mutex);
    /* The condition has occured. Set the flag and wake up any waiting threads */
    conditionMet = 1;
    printf("Wake up all waiting threads...\n");
    rc = pthread_cond_broadcast(&cond);

    rc = pthread_mutex_unlock(&mutex);

    printf("Wait for threads and cleanup\n");
    for (i=0; i<NUM_THREADS; ++i) {
        rc = pthread_join(threads[i], NULL);
    }
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    printf("Main completed\n");
    return 0;
}