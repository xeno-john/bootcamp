#include "p6.h"
#include<stdlib.h>
#include<time.h>

#define MAX_QUEUE_DIMENSION 15

int main(void)
{
    QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));
    int                                    i = 0;

    if(NULL != queue)
    {
        srand(time(NULL));

        for (i=0; i<MAX_QUEUE_DIMENSION; ++i)
        {

            if (true != push(rand()%100+1,queue))
            {
                fprintf(stderr,"Something went wrong when adding a queue member.\n");
                break;
            }

        }

        traverse(queue);

        reversed_traverse(queue);

        free(queue);
        queue=NULL;
    }
    else
    {
        fprintf(stderr,"Failed to allocate memory for the pointer that indicates the start of the queue.\n");
    }
    

    return 0;
}

