#include "p11.h"
#include <time.h>

/**
 * @fn void* initialize_engine(void)
 * @brief Allocates an internal ENGINE_DATA* struct and returns it as void*.
 * @param void
 * @return void*
 **/
void* initialize_engine(void)
{
    ENGINE_DATA *engine_data = (ENGINE_DATA*)malloc(sizeof(ENGINE_DATA));

    engine_data->is_ready = false;

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

    return (void*)engine_data;
}

/**
 * @fn int start_engine(void* engine)
 * @brief Starts the consumer thread that consumes the queue.
 * @param[in] engine ENGINE_DATA* struct.
 * @return int 
 **/
int start_engine(void* engine)
{
    pthread_create(((ENGINE_DATA*)engine)->consumer_thread, NULL, (void*)on_consume, engine);
    return 0;
}

/**
 * @fn int produce(void* engine, int index)
 * @brief A function that is called by a producer thread and pushes an element on the engine queue.
 * @param[in] engine ENGINE_DATA* struct. 
 * @param[in] index Index.
 * @return int 
 **/
int produce(void* engine, int index)
{
    pthread_mutex_lock(&((ENGINE_DATA*)engine)->mutex);

    printf ("In producer thread...\n");
    push(rand(), ((ENGINE_DATA*)engine)->q);

    pthread_mutex_unlock(&((ENGINE_DATA*)engine)->mutex);
    return 0;
}


/**
 * @fn int onConsume(void* engine, int index)
 * @brief A function that is called by a consumer thread and extracts elements and prints them.
 * @param[in] engine ENGINE_DATA* struct. 
 * @param[in] index Index.
 * @return int 
 **/
int on_consume(void *engine, int index)
{
    
    printf ("In consumer thread...\n");

    while(true)
    {

        if (true == ((ENGINE_DATA*)engine)->is_ready)
        {

            while (0 == is_empty(((ENGINE_DATA*)engine)->q))
            {
                pop(((ENGINE_DATA*)engine)->q);
            }

            break;

        }

    }

    pthread_exit(NULL);

    return 0;
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