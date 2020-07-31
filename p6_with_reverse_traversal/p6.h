#ifndef Q_H_
#define Q_H_

#include "../DBG_PRINT.h"
#include <stdbool.h>

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

bool push(int value, QUEUE *queue);
void pop(QUEUE *q);
void reversed_traverse(QUEUE *queue);
void traverse(QUEUE *q);
int is_empty(QUEUE* q);

#endif
