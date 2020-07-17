#include<stdio.h>
#include<stdint.h> // this is the library where uint32_t is found.

void printBits(uint32_t x); // declaration

// implementation.
// made no sense to work with a different header file because there is only ONE function.
void printBits(uint32_t x)
{
	int i=0;
        /* the number of bits that the number has is 8 ( because there are 8 bits in a byte )
         * times the size in bytes of the data type. So, in order to make sure that all of the
         * potential bits of the number are traversed, we use a contor value that goes to sizeof(x)*8
         */
        printf("\nThis is the number you gave written in binary representation:\n");
	for(i=0;i<sizeof(x)*8;++i)
	{
                // we use the ternary operator to write less code lines
	        printf("%u", ( (x & 0x01) == 0x01 ) ? 1 : 0 );
                /* we test the last bit, in the sense that we will do a bitwise and between the given number
                 * and a mask ( in this case, 0x01, we don't need to put it in a variable
                 * if the result is 1, we print 1
                 * else, we print 0
                 */
                x>>=1;
                /*then we shift the number one position to the right
                 * otherwise, we would be only testing the last bit
                 * for sizeof(x)*8 times.
                 */
	}
        printf("\n");
        //for aesthetics
}

int main(void)
{
	uint32_t x;
	printf("Give the value for which to print the bits: ");
	scanf("%u",&x);
	printBits(x);
	return 0;
}
