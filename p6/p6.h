#ifndef Q_H_
#define Q_H_

#include "../DBG_PRINT.h"

typedef struct _NODE
{
    int data;
    struct _NODE *next;
}NODE;

typedef struct _QUEUE
{
    NODE *start;
    NODE *end;
} QUEUE;

void push(int, QUEUE *q);
void pop(QUEUE *q);
void traverse(QUEUE *q);
int isEmpty(QUEUE* q);

#endif
