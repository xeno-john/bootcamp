#include "p9.h"

/* it says we should not use global variables
 but, as of right now
 i have no clue of doing it in other ways.
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *task(void *arg)
{
    // here we print the value we received.
    // then it increments

    // we lock the mutex to deny access if a thread already is
    // in this section executing the print and increment
    pthread_mutex_lock(&mutex);
    DBG_PRINT(5,"Argument: %d\n",(*(int*)arg)++); // critical section
    pthread_mutex_unlock(&mutex);
    // we unlock it so that the waiting thread can also do this operation
    // in this way we prevent both threads from accessing a resource
    // at the same moment of time.

    // pthread_exit() function terminates the calling thread
    // and retuns a value via retval
    pthread_exit(NULL);
}
