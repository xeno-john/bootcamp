#ifndef P8_H_
#define P8_H_

#include "../DBG_PRINT.h"
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

void *task(void *arg);

#endif
