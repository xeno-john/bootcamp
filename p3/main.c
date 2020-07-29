#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * @brief Function that receives two ints a prints a percentage.
 * @param [in] index - index here the parser is in that moment
 * @param [in] data_size - dimension of input buffer
 */
void progress_callback(int index, int data_size);

/**
 * @brief Function that parses a char* character by character and prints the ascii value of it, also the progress made (%).
 * @param [in] p_callback - pointer to the function that prints the percentage of the progress
 * @param [in] input_data - char* where we have stocked our input data
 * @param [in] data_size - dimension of input buffer
 */
void handle_data( void (*p_callback)(int, int), char* input_data, int data_size );

void handle_data( void (*p_callback)(int, int), char* input_data, int data_size )
{
    int i=0;

    while ('\0' != input_data[i] && i<data_size) /* either we reach the end of the string(\0), or the maximum limit of bytes. */
    {
        printf("%3d",input_data[i]);
        ++i;
        p_callback(i,strlen(input_data));
    }

}

void progress_callback(int index, int data_size)
{ 
    /* %6.2f to be alligned perfectly one under another */
    printf(" | %6.2f%%\n", 100*(float)index/(float)data_size);
}

int main(void)
{
    int          data_size = 0;
    char*  input_buffer = NULL;
    int  continuation_flag = 1;
    printf("Please give the size in bytes of the data you want to send.\n");
    printf("Keep in mind that one byte must be left for the \\0 special character ( string terminator ) :");
    
    if (0 == scanf("%d",&data_size))
    {
        fprintf(stderr,"Failed to read data_size.\n");
        continuation_flag = 0;
    }
    else
    {
        input_buffer = (char*)malloc(data_size);
    
        if (NULL == input_buffer)
        {
            fprintf(stderr,"Failed to allocate memory for the input_buffer.\n");
            continuation_flag = 0;
        }
        else
        {
            printf("\nEnter the data in the buffer: ");
            getchar();

            if (NULL != fgets(input_buffer,data_size,stdin))
            {

                if ('\n' == input_buffer[strlen(input_buffer)-1])
                {
                    input_buffer[strlen(input_buffer)-1] = '\0';
                }

            }
            else
            {
                fprintf(stderr,"Reading the input_buffer failed.\n");
            }
            
        }
        
    }
    
    /* clear the stdin buffer in order to avoid reading before we actually want it */

    if (1 == continuation_flag)
    {
        handle_data(&progress_callback,input_buffer,data_size);
        free(input_buffer);
        input_buffer = NULL;
    }

    return 0;
}
