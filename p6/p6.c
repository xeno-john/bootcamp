#include "p6.h"

#include <stdio.h>
#include <stdlib.h>

/**
 *  @brief Function that introduces data in the queue
 *  @param [in] value - value which will be introduced in the queue
 *  @param [in] queue - pointer to the queue in which the data is going to be introduced
 *  @return return_value - boolean true if push was succesfull, false otherwise
 */
bool push(int value, QUEUE *queue)
{
    NODE *aux = (NODE*)malloc(sizeof(NODE));
    bool return_value = true;
    
    if (NULL != aux)
    {
        aux->data = value;
        aux->next = NULL;

        if (1 == is_empty(queue))
        {
            queue->start = aux;
            queue->end = aux;
        }
        else
        {
            queue->end->next = aux;
            queue->end = aux;
        }

    }
    else
    {
        fprintf(stderr,"Failed to allocate auxiliary value in push function.\n");
        return_value = false;
    }
    
    return return_value;
}

/**
 *  @brief Function that removes data from the queue.
 *  @param [in] queue - pointer to the queue in which the data is going to be removed
 */
void pop(QUEUE *queue)
{

    if (1 == is_empty(queue))
    {
        fprintf(stderr,"queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        NODE *temp = queue->start;
        queue->start = temp->next; 
        DBG_PRINT(5,"Popped out %d\n",temp->data);
        free(temp);
        temp=0;
    }

}

/**
 *  @brief Function that traverses the queue and prints all the current data.
 *  @param [in] queue - pointer to the queue which is going to be printed.
 */
void traverse(QUEUE *queue)
{
    printf("The queue:\n");

    if (0 == is_empty(queue))
    {
        NODE *temp = queue->start;
        
        while (NULL != temp)
        {
            DBG_PRINT(1,"%d\n",temp->data); 
            temp = temp->next; 
        }

        free(temp);
        temp = NULL;
    }
    
}

/**
 *  @brief Function that retruns 1 (true) if the given queue is empty, and 0 otherwise
 *  @param [in] queue - pointer to the queue which is going to be tested for emptiness
 *  @return empty_flag - is 1 if given queue has no elements, 0 otherwise
 */
int is_empty(QUEUE *queue)
{
    int empty_flag = 0;

    if (NULL == queue->start)
    {
        empty_flag = 1;
    }

    return empty_flag;
}


