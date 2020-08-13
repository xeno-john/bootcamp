#ifndef P12_H_
#define P12_H_

#include <stdio.h>
#include <stdlib.h>
#include "../DBG_PRINT.h"

typedef struct _NODE_DATA
{
    int nr_of_occurences;
    char word[256];
}NODE_DATA;

typedef struct _NODE
{
    NODE_DATA content;
    struct _NODE *next;
}NODE;


NODE* insert_in_list(NODE* head, char to_be_inserted[]);
NODE* init_list_node();
void traverse(NODE* head);

#endif