#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <errno.h>

/**
 * @brief Function that receives an uint32_t and prints the bit configuration of that number.
 * @param [in] input_value - the value gave by the user for which we will print the bits 
 */
void printBits(uint32_t input_value);

void printBits(uint32_t input_value)
{
	int i = 0;
        int nr_of_bits = sizeof(input_value)*8-1;

        printf("\nThis is the number you gave written in binary representation:\n");

	for(i=nr_of_bits;i>=0;--i)
	{
	        printf("%u", ( (1 << i) & input_value ) ? 1 : 0 );
                if( i%4 == 0 )
                {
                        printf("\t");
                }
	}

        printf("\n");
}

int main(void)
{
	uint32_t           input_value = 0; 
        char      input_buffer[1024] = {0}; 
        char                *endptr = NULL;
        int         was_read_correctly = 1; 
        errno =                          0; 

	printf("Give the value for which to print the bits: ");

        /* 
         * Presuming wrong input from user, it does not signal:
         * - number that exceeds the range of uint_32 (remains to be fixed)
         * For example: 4294967295 is the max value of uint_32 ( and this can be also confirmed by the output )
         * If bigger numbers are entered the actual value seems to reset ( go back to 0 and upwards.)
         */

        if (NULL == fgets(input_buffer, 1024, stdin)) 
        {
                was_read_correctly = 0;
        }
        else
        {       if ('-' == input_buffer[0])
                {
                        fprintf(stderr,"Negative number not allowed.\n");
                        was_read_correctly = 0;
                }
        }

        if (1 == was_read_correctly)
        {
                input_value = strtol(input_buffer, &endptr, 10);

                if (ERANGE == errno) 
                {
                        fprintf(stderr,"Sorry, this number is too small or too large.\n");
                        was_read_correctly = 0;
                }
                else if (endptr == input_buffer)
                {
                        fprintf(stderr,"Incorrect input.\n(Entered characters or characters and digits.)\n");
                        was_read_correctly = 0;
                }
                else if (*endptr && '\n' != *endptr)
                {
                        fprintf(stderr,"Input didn't get wholely converted.\n(Entered digits and characters)\n");
                        was_read_correctly = 0;
                }

        }
        else
        {
                fprintf(stderr,"Input was not read correctly.\n");
        }

        if (1 == was_read_correctly)
        {
	        printBits(input_value);
        }

	return 0;
}