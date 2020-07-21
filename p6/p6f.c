#include "p6.h"

#include <stdio.h>
#include <stdlib.h>

void push(int value, QUEUE *q)
{
    NODE *aux = (NODE*)malloc(sizeof(NODE));
    aux->data = value;
    aux->next = NULL;

    if(isEmpty(q) == 1)
    {
        //if the queue is empty
        // we initialize the pointer in the starting position
        q->start = aux;
        // the rear pointer will be the same as the front one
        // because we only have one element
        q->end = aux;
    }
    else
    {
        // otherwise, we create the connection in the rear of the
        q->end->next = aux;
        q->end = aux;
    }

}

void pop(QUEUE *q)
{
    // if the queue has no elements
    // we terminate the program.
    if(isEmpty(q) == 1)
    {
        fprintf(stderr,"Q is empty.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // otherwise 
        // we use a temp value to actually print the value we pop
        NODE *temp = q->start;
        q->start = temp->next; // here we modify the starting position
        // because one element is eliminated
        DBG_PRINT(5,"Popped out %d\n",temp->data);
        free(temp); // free memory
        temp=0;
    }

}

void traverse(QUEUE *q)
{
    printf("The queue:\n");
    // if we got any elements left
    if(isEmpty(q) == 0)
    {
        // we use a temporary value initialized with the starting point
        NODE *temp = q->start;
        // until we reach the null value ( end of the queue)
        while(temp != NULL)
        {
            DBG_PRINT(1,"%d\n",temp->data); // we print the element
            temp = temp->next; // then we move to the next one in the Q
        }
        free(temp);
    }
}

int isEmpty(QUEUE *q)
{
    // we use the ternary operator to return
    // 1 if the queue is empty
    // 0 if it is not
    return ((q->start == NULL) ? 1 : 0);
}


