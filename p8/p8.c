#include "p8.h"

void *task(void *arg)
{
    // we explicitly cast the value to long (8 bytes) because
    // the void pointer is 8 bytes in size
    // and int type uses 4 bytes

    long tid = (long)arg;

    // here we print the value we received.
    DBG_PRINT(5,"Argument: %li\n",tid);
    
    // pthread_exit() function terminates the calling thread
    // and retuns a value via retval
    pthread_exit(NULL);
}
