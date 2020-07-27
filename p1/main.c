#include<stdio.h>
#include<stdint.h> /* this is the library where uint32_t is found. */
#include<stdlib.h>
#include <errno.h>

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
         * potential bits of the number are traversed, we use a contor value that goes from sizeof(x)*8-1
         * to 0.
         */
        printf("\nThis is the number you gave written in binary representation:\n");
	for(i=sizeof(givenValue)*8-1;i>=0;--i)
	{
	        printf("%u", ( (1 << i) & givenValue ) ? 1 : 0 );
                /* this method does bitwsie and between the given number
                 * and '1' shifted left by 'i' positions
                 * in this way, we traverse the number from right to left
                 * resulting in a correct output.
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
	uint32_t givenValue = 0; /*!< The number that we'll be printing the bits of. */
        char buf[1024]; /*!< Buffer used to read the number with the help of fgets and strtol. */
        char *endptr; /*! endptr is set to point at the first character that couldn't
        be converted. So we have a way to check whether the whole string was converted. */
	printf("Give the value for which to print the bits: ");
        /* http://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
         * used guide from here.
         * fgets seems to be as efficient as scanf previously was but with 
         * more lines of code.
         * Signaled errors:
         * - if user tries to input characters
         * - if number is numerically out of range ( assume max 64 bit number )
         * It does not signal:
         * - negative number input (fixed with an if unrelated to fgets)
         * - number that exceeds the range of uint_32 (remains to be fixed)
         * For example: 4294967295 is the max value of uint_32 ( and this can be also confirmed by the output )
         * which shows 1111 [..] 1111
         * But when the users enters 4294967296, the numbers is represented as
         * 0000 [..] 0000 (some sort of reset.)
         */
        if (!fgets(buf, 1024, stdin)) /* fgets returns NULL if the input was not read correctly. */
        {
            /* reading input failed: */
            fprintf(stderr,"Reading input failed.\n");
            exit(EXIT_FAILURE);
        }
        /* have fixed negative number input with this 
         * condition
         */
        if( buf[0] == '-' )
        {
                fprintf(stderr,"Negative number not allowed.\n");
                exit(EXIT_FAILURE);
        }
        errno = 0; /* reset error number */
        givenValue = strtol(buf, &endptr, 10);
        if (errno == ERANGE) /* numerical out of range. NOT out of range of the respective data type. */
        {
            fprintf(stderr,"Sorry, this number is too small or too large.\n");
            exit(EXIT_FAILURE);
        }
        else if (endptr == buf)
        {
            /* incorrect input */
            fprintf(stderr,"Incorrect input.\n(Entered characters or characters and digits.)\n");
            exit(EXIT_FAILURE);
        }
        else if (*endptr && *endptr != '\n')
        {
            /* *endptr is neither end of string nor newline,
             * so we didn't convert the *whole* input
             */
            fprintf(stderr,"Input didn't get wholely converted.\n(Entered digits and characters)\n");
            exit(EXIT_FAILURE);
        }
	printBits(givenValue);
	return 0;
}