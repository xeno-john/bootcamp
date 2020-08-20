#include "p12.h"

int main(void)
{
    MAP *map = initialize_map(MAX_MAP_DIMENSION);
    unsigned int            current_map_size = 0;
    char                          buffer[256]={};
    const char                   SEPARATOR[]=" ";
    char                          *parser = NULL;
    FILE*                      input_file = NULL;

    input_file = fopen("input.txt","r");

    if (NULL != map)
    {

        if ( NULL == input_file)
        {
            fprintf(stderr,"Failed to open input file.\n");
        }
        else
        {

            if (NULL != fgets(buffer,256,input_file))
            {
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
                    current_map_size = insert(map,parser);
                    parser = strtok(NULL,SEPARATOR);
                }

            }

        }
    
        sort(map,current_map_size);
        print(map,current_map_size);

        free(map);
        map = NULL;

        free(parser);
        parser = NULL;
    }
    else
    {
        fprintf(stderr,"Failed to allocate memory for the map.\n");
    }
    
    if (NULL != input_file)
    {
        fclose(input_file);
        input_file = NULL;
    }

    return 0;
}