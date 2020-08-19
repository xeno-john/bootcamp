#include "p12.h"

MAP *initialize_map(unsigned int map_size)
{
    MAP* created_map = (MAP*)malloc(map_size*sizeof(MAP));
    unsigned int                                      i=0;

    for (i=0; i<map_size; ++i)
    {
        (created_map+i)->nr_of_occurences=0;
    }

    return created_map;
}

unsigned int insert(MAP *map, char key[])
{
    unsigned int                i = 0;
    unsigned int       found_flag = 0;
    static unsigned int curr_size = 0;
    
    for(i=0; i<curr_size; ++i)
    {
        if (0 == strncmp((map+i)->key,key,strlen((map+i)->key)))
        {
            found_flag = 1;
            (map+i)->nr_of_occurences++;
            break;
        }
        
    }

    if (0 == found_flag)
    {
        strncpy((map+curr_size)->key,key,strlen(key));
        (map+curr_size)->nr_of_occurences = 1;
        curr_size ++;
    }

    return curr_size;
}

void sort(MAP *map, unsigned int size)
{
    int swapped = 0;

    do
    { 
        swapped        = 0;
        unsigned int i = 0;
    
        for(i=0; i<size-1; ++i) 
        { 

            if ((map+i)->nr_of_occurences<(map+i+1)->nr_of_occurences) 
            {
                unsigned int aux_nr_of_occurences = (map+i)->nr_of_occurences;
                char aux_key[256];

                (map+i)->nr_of_occurences=(map+i+1)->nr_of_occurences;
                (map+i+1)->nr_of_occurences=aux_nr_of_occurences;

                strcpy(aux_key,(map+i)->key);
                strcpy((map+i)->key,(map+i+1)->key);
                strcpy((map+i+1)->key,aux_key);

                swapped = 1; 
            } 

        } 

    } 
    while (0 != swapped);
    
}

void print(MAP *map, unsigned int size)
{
    unsigned int i = 0;

    printf("\nResult:\n");
    for (i=0; i<size; ++i)
    {

        if (1 != (map+i)->nr_of_occurences)
        {
            DBG_PRINT(5,"%d occurences of '%s'\n",(map+i)->nr_of_occurences,(map+i)->key);
        }
        else
        {
            DBG_PRINT(5,"%d occurence of '%s'\n",(map+i)->nr_of_occurences,(map+i)->key);
        }

    }

}