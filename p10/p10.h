#ifndef P10_H_
#define P10_H_

#include "../DBG_PRINT.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

extern int conditionMet;
extern pthread_cond_t      cond;
extern pthread_mutex_t     mutex;

void *task(void *arg);

#endif