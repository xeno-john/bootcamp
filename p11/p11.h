#include "queueHeader.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _ENGINE_DATA
{
    QUEUE* q;
    pthread_t* consumer_thread;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool is_ready;
}ENGINE_DATA;

#define NUMBER_OF_PRODUCERS 10

void* initialize_engine(void);
int start_engine(void* engine);
int produce(void* engine, int index);
int on_consume(void *engine, int index);
void stop_engine(void* engine);
void destroy_engine(void* engine);
