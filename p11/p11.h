#include "queueHeader.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _ENGINE_DATA
{
    QUEUE* q;
    pthread_t* consumer_thread;
    pthread_mutex_t mutex;
    bool is_ready;
    bool consumer_online;
}ENGINE_DATA;

typedef struct _ARGS
{
    ENGINE_DATA* engine;
    unsigned long index;

}ARGS;

#define NUMBER_OF_PRODUCERS 10

void *initialize_engine(void);
void start_engine(void* engine);
void *produce(void* arguments);
void *on_consume(void *arguments);
void stop_engine(void* engine);
void destroy_engine(void* engine);
