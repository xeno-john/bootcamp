#include "p12.h"
#include<string.h>

int main(void)
{
    NODE*       list_head = NULL;
    char          buffer[256]={};
    const char SEPARATOR[]=" ";
    char          *parser = NULL;
    FILE*      input_file = NULL;

    input_file = fopen("input.txt","r");

    if ( NULL == input_file)
    {
        fprintf(stderr,"Failed to open input file.\n");
    }
    else
    {

        if (NULL != fgets(buffer,256,input_file))
        {
            printf("Succesfully read from an input file.\n");
            fclose(input_file);
            input_file = NULL;
            
            int i = 0;

            /* we convert the input string to lowercase if necessary. */
            for(i = 0; i<strlen(buffer); ++i)
            {
                        
                if(buffer[i]>=65 && buffer[i]<=92)
                {
                            buffer[i]+=32;
                }
                else if(10 == buffer[i])
                {
                    buffer[i]=32;
                }

            }

            parser = strtok(buffer,SEPARATOR);

            while(NULL != parser)
            {
                list_head = insert_in_list(list_head,parser);
                parser = strtok(NULL,SEPARATOR);
            }

        }

        printf("Result:\n");
        traverse(list_head);

        free(list_head);
        list_head = NULL;

    }

    return 0;
}