#ifndef P12_W_MAPS_H_
#define P12_W_MAPS_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../DBG_PRINT.h"

#define MAX_MAP_DIMENSION 16384
#define MAX_NR_OF_CHARACTERS 4096

typedef struct _MAP
{
    int nr_of_occurences;
    char key[MAX_NR_OF_CHARACTERS];
}MAP;

MAP *initialize_map(unsigned int map_size);
unsigned int insert(MAP *map, char key[]);
void sort(MAP *map, unsigned int size);
void print(MAP *map, unsigned int size);

#endif
