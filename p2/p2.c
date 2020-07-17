#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

uint32_t getValue(char* buffer, int offset, int bufferSize);

uint32_t getValue(char* buffer, int offset, int bufferSize)
{
    int i=0;
    uint32_t result=0;
    if(offset<bufferSize) // if offset is bigger it makes no sense to continue
    {
        /*
         * we start from the offset index
         * and go to bufferSize-1
         */
        for(i=offset;i<bufferSize; ++i)
        {
            /* we could be in the situation in which the input is a number smaller than the
             * bufferSize
             * so we also need to test if the current character is '\0'
             * otherwise the result would be faulty
             * in the sense that there would be trash values added to it
             */
            if( buffer[i] == '\0' )
            {
                break;
            }
            else
            {
                result=result*10+(buffer[i]-'0');
                /* we multiply by 10 to add another decimal to the number
                 * which works fine with 0 ( initial value ) too
                 * then we sum the result with the decimal we are currently at. 
                 * the conversion from char to int is done using -'0'
                 */
            }
        }
    }
    else
    {
        fprintf(stderr,"Offset bigger than number size.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(void)
{
    int result = 0;
    int bufferSize = 0;
    int offset = 0;
    char* buff = 0;

    printf("What is the size of the buffer? ");
    scanf("%d",&bufferSize);
   
    // allocating memory for the buffer
    buff = (char*)malloc(bufferSize); // size of char is 1 so no point in multiplying the buffer size with that.
    if( buff == 0 ) // should be verified so nothing bad happens when allocation fails.
    {
        fprintf(stderr,"Error when allocating memory for the buffer.\n");
        exit(EXIT_FAILURE); // if allocation fails the program is closed and error is prompted on screen.
    }
    
    getchar(); // we use this in order to clear the reading buffer.
    
    printf("Give the number to be put in the buffer: ");
    fgets(buff,bufferSize,stdin);

    /* if what we read is smaller than the bufferSize we gave,
     * fgets will also read the \n(enter)
     * so it needs to be removed explicitly.
     */
    if(buff[strlen(buff)-1] == '\n')
    {
        buff[strlen(buff)-1] = '\0';
    }
       
    printf("Give the offset you want to have: ");
    scanf("%d",&offset);
    
    result = getValue(buff,offset,bufferSize);
    printf("The result is: %d\n",result);
    return 0;
}
