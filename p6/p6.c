#include "p6.h"
#include<stdlib.h>
#include<time.h>

#define DIM 15

int main(void)
{
    int i = 0;
    QUEUE *q = (QUEUE*)malloc(sizeof(QUEUE));
    srand(time(NULL));
    for(i=0; i<DIM; ++i)
    {
        push(rand()%100+1,q);
    }
    traverse(q);
    return 0;
}

