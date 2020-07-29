#include "p6.h"
#include<stdlib.h>
#include<time.h>

#define DIM 15
/* dummy comment please remove */
int main(void)
{
    int i = 0;
    QUEUE *q = (QUEUE*)malloc(sizeof(QUEUE));
    //add random elements into the queue.
    srand(time(NULL));
    for(i=0; i<DIM; ++i)
    {
        push(rand()%100+1,q);
    }
    traverse(q); // print the elements
    free(q); // free memory .
    q=0;
    return 0;
}

