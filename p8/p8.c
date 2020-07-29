#include "p8.h"

void *task(void *arg)
{
    long thread_id = (long)arg;

    DBG_PRINT(5,"Argument: %li\n",thread_id);
    
    pthread_exit(NULL);
}
