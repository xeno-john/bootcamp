#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>


/**
 * @brief The function that handles the given task.
 * @param [in] input_buffer - the value gave by the user for which we will print the bits
 * @param [in] offset - index from where the function will parse
 * @param [in] bufferSize - max dimension of input_buffer 
 */
uint32_t getValue(char* input_buffer, int offset, int bufferSize);


/*!
 *  \fn uint32_t getValue(char* input_buffer, int offset, int bufferSize)
 *  \brief The function that handles the given task.
 *  \param input_buffer The variable from which we are to read and produce the asked output.
 *  \param offset A number that indicates the position from which to start doing the task.
 *  \param bufferSize The actual size of the buffer variable. Useful in comparing it to the offset.
 */
uint32_t getValue(char* input_buffer, int offset, int bufferSize)
{
    int                   i=0; 
    uint32_t       result = 0; 
    int found_number_flag = 0; 

    if(offset<bufferSize)
    {

        for(i=offset;i<bufferSize; ++i)
        {

            if ('\0' == input_buffer[i])
            {
                break;
            }
            else
            {
                /* 
                 * interval represents ascii coding for 0-9 digits.
                 * flag is used to stop parsing after we found a number.
                 */
                if (input_buffer[i]>=48 && input_buffer[i]<=57)
                {
                    found_number_flag = 1;
                    result=result*10+(input_buffer[i]-'0');
                }
                /* if it is NOT a digit */
                else
                {
                    /* but we have parsed digits in the past */
                    if (1 == found_number_flag)
                    {
                        break;
                    }

                }
                
            }

        }
        
    }
    else
    {
        result = -1;
    }

    return result;
}

int main(void)
{
    int             result = 0;
    int         bufferSize = 0;
    int             offset = 0;
    char*  input_buffer = NULL;
    int  continuation_flag = 1;

    printf("What is the size of the buffer? ");
    
    if (0 == scanf("%d",&bufferSize))
    {
        fprintf(stderr,"Failed to read bufferSize.");
        continuation_flag = 0;
    }
    else
    {
        input_buffer = (char*)malloc(bufferSize); 

        if (NULL == input_buffer) 
        {
            fprintf(stderr,"Error when allocating memory for the buffer.\n");
            continuation_flag = 0;
        }
        else
        {
            getchar(); 

            printf("Give the string to be put in the buffer: ");

            if (NULL == fgets(input_buffer,bufferSize,stdin))
            {
                fprintf(stderr,"Failed to read in the buffer.\n");
                continuation_flag = 0;
            }
            else
            {

                if('\n' == input_buffer[strlen(input_buffer)-1])
                {
                    input_buffer[strlen(input_buffer)-1] = '\0';
                }

                printf("Give the offset you want to have: ");
        
                if (0 == scanf("%d",&offset))
                {
                    fprintf(stderr,"Failed to read offset.");
                    continuation_flag = 0;
                }

            } 

        }
    
    }

    if (1 == continuation_flag)
    {
        result = getValue(input_buffer,offset,bufferSize);

        if (-1 != result)
        {
            printf("Result: %d\n",result);
        }
        else
        {
            fprintf(stderr,"Offset was bigger than the buffer size.\n");
        }

        free(input_buffer);
        input_buffer = NULL;
    }

    return 0;
}
