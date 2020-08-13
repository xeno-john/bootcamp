#include "p11.h"
#include <time.h>

/**
 * @fn void* initialize_engine(void)
 * @brief Allocates an internal ENGINE_DATA* struct and returns it as void*.
 * @param void
 * @return void*
 **/
void *initialize_engine(void)
{
    ENGINE_DATA *engine_data = (ENGINE_DATA*)malloc(sizeof(ENGINE_DATA));

    if( NULL != engine_data)
    {
        engine_data->is_ready = false;
        engine_data->consumer_online = true;

        engine_data->q = (QUEUE*)malloc(sizeof(QUEUE));

        if (NULL == engine_data->q)
        {
            fprintf(stderr, "Error when allocating memory for the engine_data.q!");
        }

        engine_data->consumer_thread = (pthread_t*)malloc(sizeof(pthread_t));

        if (NULL == engine_data->consumer_thread)
        {
            fprintf(stderr, "Error when allocating memory for the engine_data.consumer_thread!");
        }

    }
    else
    {
        fprintf(stderr,"Failed to allocate memory for engine_data.\n");
    }
    

    return (void*)engine_data;
}

/**
 * @fn int start_engine(void* engine)
 * @brief Starts the consumer thread that consumes the queue.
 * @param[in] void *arguments - a struct that contains an ENGINE_DATA* and an index
 * @return void
 **/
void start_engine(void* arguments)
{
    int pthread_error = pthread_create(((ARGS*)arguments)->engine->consumer_thread, NULL, on_consume, arguments);

    if (0 != pthread_error)
    {
        DBG_PRINT(1, "Error! Code for pthread_create: %d", pthread_error);
    }
    
}

/**
 * @fn void produce(void* arguments)
 * @brief A function that is called by a producer thread and pushes an element on the engine queue.
 * @param[in] void *arguments - a struct that contains an ENGINE_DATA* and an index
 * @return void
 **/
void *produce(void* arguments)
{
    pthread_mutex_lock(&((ARGS*)arguments)->engine->mutex);
    
    ((ARGS*)arguments)->index = rand();

    printf ("\nIn producer thread.\nId: %lu\nIndex: %lu\n",pthread_self(),((ARGS*)arguments)->index);
    push(((ARGS*)arguments)->index, ((ARGS*)arguments)->engine->q);

    pthread_mutex_unlock(&((ARGS*)arguments)->engine->mutex);

    return NULL;
}


/**
 * @fn void on_consume(void *arguments)
 * @brief A function that is called by a consumer thread and extracts elements and prints them.
 * @param[in] void *arguments - a struct that contains an ENGINE_DATA* and an index
 * @return void
 **/
void *on_consume(void *arguments)
{
    
    printf ("In consumer thread.\nThread id: %lu.\nIndex: %lu.\n",pthread_self(),((ARGS*)arguments)->index);
    
    while (true == ((ARGS*)arguments)->engine->consumer_online)
    {

        while (false == ((ARGS*)arguments)->engine->is_ready)
        {
        }


        while (0 == is_empty(((ARGS*)arguments)->engine->q))
        {
            pop(((ARGS*)arguments)->engine->q);
        }

    }

    return NULL;
}

/**
 * @fn stop_engine(void* engine)
 * @brief Waits for the consumer thread to finish its task for it to be stopped.
 * @param[in] engine ENGINE_DATA* struct.
 * @return void 
 **/
void stop_engine(void* engine)
{
    printf("\nStopped engine.\n");

    ((ENGINE_DATA*)engine)->consumer_online = false;
    
    int pthread_error = pthread_join(*((ENGINE_DATA*)engine)->consumer_thread, NULL);

    if (0 != pthread_error)
    {
        DBG_PRINT(1, "Error! Code for pthread_join: %d", pthread_error);
    }

}

/**
 * @fn void destroy_engine(void* engine)
 * @brief Deallocates ENGINE_DATA* members created with initialize_engine.
 * @param[in] engine ENGINE_DATA* struct.
 * @return void 
 **/
void destroy_engine(void* engine)
{
    printf("\nDestroyed engine.\n");
    
    if (NULL != ((ENGINE_DATA*)engine)->q)
    {
        free(((ENGINE_DATA*)engine)->q);
        ((ENGINE_DATA*)engine)->q = NULL;
    }

    if (NULL != ((ENGINE_DATA*)engine)->consumer_thread)
    {
        free(((ENGINE_DATA*)engine)->consumer_thread);
        ((ENGINE_DATA*)engine)->consumer_thread = NULL;
    }

    pthread_mutex_destroy(&((ENGINE_DATA*)engine)->mutex);

}