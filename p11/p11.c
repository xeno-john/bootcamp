#include "p11.h"
#include <time.h>

/**
 * @fn void* initializeEngine(void)
 * @brief Allocates an internal ENGINE_DATA* struct and returns it as void*.
 * @param void
 * @return void*
 **/
void* initialize_engine(void)
{
    int pthread_error = 0;
    ENGINE_DATA *engine_data = (ENGINE_DATA*)malloc(sizeof(ENGINE_DATA));

    engine_data->is_ready = false;
    engine_data->nr_of_elements = 0;

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

    pthread_error = pthread_cond_init(&((ENGINE_DATA*)engine_data)->cond, NULL);
    if (0 != pthread_error) 
    {
        DBG_PRINT(1, "Error! Code for pthread_cond_init: %d", pthread_error);
    }

    return (void*)engine_data;
}

/**
 * @fn int startEngine(void* engine)
 * @brief Starts the consumer thread that consumes the queue.
 * @param[in] engine ENGINE_DATA* struct.
 * @return int 
 **/
int start_engine(void* engine)
{

    pthread_create(((ENGINE_DATA*)engine)->consumer_thread, NULL, (void*)on_consume, engine);
    
    return 0;
}

int produce(void* engine, int index)
{

    int rand_value = rand();

    pthread_mutex_lock(&((ENGINE_DATA*)engine)->mutex);

    printf ("In producer thread...\n");

    push(rand_value, ((ENGINE_DATA*)engine)->q);

    ((ENGINE_DATA*)engine)->nr_of_elements ++;

    traverse(((ENGINE_DATA*)engine)->q);

    while (false != ((ENGINE_DATA*)engine)->is_ready)
    {
        pthread_cond_wait (&((ENGINE_DATA*)engine)->cond, &((ENGINE_DATA*)engine)->mutex);
    }

    ((ENGINE_DATA*)engine)->is_ready = true;

    pthread_cond_signal (&((ENGINE_DATA*)engine)->cond);

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

    pthread_mutex_lock(&((ENGINE_DATA*)engine)->mutex);
    
    printf ("In consumer thread...\n");

    while (false == ((ENGINE_DATA*)engine)->is_ready)
    {
        pthread_cond_wait (&((ENGINE_DATA*)engine)->cond, &((ENGINE_DATA*)engine)->mutex);
    }


    if (0 == is_empty(((ENGINE_DATA*)engine)->q))
    {
        pop(((ENGINE_DATA*)engine)->q);
    }

    pthread_cond_signal (&((ENGINE_DATA*)engine)->cond);

    pthread_mutex_unlock(&((ENGINE_DATA*)engine)->mutex);

    return 0;
}

void stop_engine(void* engine)
{
    int pthread_error = pthread_join(*((ENGINE_DATA*)engine)->consumer_thread, NULL);

    if (0 != pthread_error)
    {
        DBG_PRINT(1, "Error! Code for pthread_join: %d", pthread_error);
    }
}

/**
 * \fn void destroyEngine(void* engine)
 * \brief Deallocates ENGINE_DATA* members created with initializeEngine and struct.
 * \param[in] engine ENGINE_DATA* struct.
 * \return void 
 **/
void destroy_engine(void* engine)
{

    if (NULL != ((ENGINE_DATA*)engine)->q)
    {
        free(((ENGINE_DATA*)engine)->q);
        ((ENGINE_DATA*)engine)->q = NULL;
    }

    if (NULL != engine)
    {
        free(engine);
        engine = NULL;
    }

}