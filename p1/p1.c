#include<stdio.h>
#include<stdint.h> /* this is the library where uint32_t is found. */
#include<stdlib.h>

void printBits(uint32_t x);

/*!
 *  \fn void printBits(uint32_t givenValue)
 *  \brief The function that handles the given task (printing the bits of a given number.)
 *  \param givenValue Value that we will print the bits of.
 */
void printBits(uint32_t givenValue)
{
	int i = 0;
        /* the number of bits that the number has is 8 ( because there are 8 bits in a byte )
         * times the size in bytes of the data type. So, in order to make sure that all of the
         * potential bits of the number are traversed, we use a contor value that goes to sizeof(x)*8
         */
        printf("\nThis is the number you gave written in binary representation:\n");
	for(i=sizeof(givenValue)*8-1;i>=0;--i)
	{
	        printf("%u", ( (1 << i) & givenValue ) ? 1 : 0 );
                /* we test the last bit, in the sense that we will do a bitwise and between the given number
                 * and a mask ( in this case, 0x01, we don't need to put it in a variable
                 * if the result is 1, we print 1
                 * else, we print 0
                 */
                if( i%4 == 0 )
                {
                        printf("\t");
                }
	}
        printf("\n");
}

int main(void)
{
        /* remains to implement the part in which i validate the input the user gave
         * -> alternatives to scanf (errno, limits, etc haven't worked)
         */
	uint32_t givenValue = 0;
	printf("Give the value for which to print the bits: ");
        /* we use the return value of scanf to see if what the user gave 
         * is actually a number.
         * - does not work in the case the user gives negative numbers
         *   or numbers that are out of the domain of representation of uint_32
         */
        if(scanf("%u",&givenValue) == 0 ) /* scanf returns how many of the given values were read correctly */
        {
                fprintf(stderr,"Incorrect value given.\n");
                exit(EXIT_FAILURE);
        }
	printBits(givenValue);
	return 0;
}