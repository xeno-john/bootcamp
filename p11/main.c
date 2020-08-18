#include "p11.h"

int main(void)
{
    ENGINE_DATA                           *e_data = NULL;
    int                                            i = 0;
    pthread_t      producer_threads[NUMBER_OF_PRODUCERS];
    int                                pthread_error = 0;
    int                            continuation_flag = 1;
    ARGS                               *arguments = NULL;

    e_data = (ENGINE_DATA*)initialize_engine();

    if (NULL == e_data)
    {
        continuation_flag = 0;
    }
    else
    {
        arguments = (ARGS*)malloc(sizeof(ARGS));

        if (NULL == arguments)
        {
            continuation_flag = 0;
        }
        else
        {
            arguments->engine = e_data;
        }

    }
    

    if (1 == continuation_flag)
    {
        start_engine(arguments);

        for (i = 0; i < NUMBER_OF_PRODUCERS; i++)
        {
            pthread_error = pthread_create(&producer_threads[i], NULL, produce, arguments);
            
            if (0 != pthread_error)
            {
                DBG_PRINT(1, "Error! Code for pthread_create: %d", pthread_error);
                continuation_flag = 0;
                break;
            }

        }
        
        for (i = 0; i < NUMBER_OF_PRODUCERS; i++)
        {
            
            if (1 == continuation_flag)
            {
                pthread_error = pthread_join(producer_threads[i], NULL);

                if (0 != pthread_error)
                {
                    DBG_PRINT(1, "Error! Code for pthread_join: %d", pthread_error);
                }
                
            }

        }

        e_data->is_ready = true;

        sleep(1); /* otherwise we might free the memory before the consumer is done */
        
        stop_engine((void*)e_data);
        destroy_engine((void*)e_data);

        free(e_data);
        e_data = NULL;

        free(arguments);
        arguments = NULL;
    }

    return 0;    
}