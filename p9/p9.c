#include "p9.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *task(void *arg)
{
    pthread_mutex_lock(&mutex);

    DBG_PRINT(5,"Argument: %d\n",(*(int*)arg)++); /* critical section */

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
