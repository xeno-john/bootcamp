#include "p1.h"

#define NUM_OF_BITS 32

char* print_bits(uint32_t input_value)
{
	int i = 0;
    int nr_of_bits = sizeof(input_value)*8-1;
    char *number_representation = (char*)malloc(NUM_OF_BITS);
    memset(number_representation,'0',32);
    
    if (NULL != number_representation)
    {

        for(i=nr_of_bits;i>=0;--i)
        {
                /* for testing purpose */
                number_representation[31-i] = ( (1 << i) & input_value ) ? '1' : '0';
        }
                
        number_representation[NUM_OF_BITS]='\0';
        printf("\n");

    }
    else
    {
        fprintf(stderr,"Failed to allocate number_representation at line %d",__LINE__);
    }
        
    /* returns NULL anyway if it fails to allocate memory*/
    return number_representation;
}