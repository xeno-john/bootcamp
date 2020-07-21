#include "p10.h"

/* it says we should not use global variables
 but, as of right now
 i have no clue of doing it in other ways.
*/

void *task(void *arg)
{
    int rc = 0;
    printf("%d",rc);
    rc = pthread_mutex_lock(&mutex);

    long tid = (long)arg;
    while(conditionMet == 0)
    {
        DBG_PRINT(5,"Thread %li doing stuff.\n",tid);
        rc = pthread_cond_wait(&cond,&mutex);
    }    

    rc = pthread_mutex_unlock(&mutex);
    // pthread_exit() function terminates the calling thread
    // and retuns a value via retval
    pthread_exit(NULL);
}
