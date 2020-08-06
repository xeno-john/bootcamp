#ifndef P9_H_
#define P9_H_

#include "../DBG_PRINT.h"
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 100

void *task(void *arg);

#endif
