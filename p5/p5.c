#include "p5.h"
#include<stdlib.h>

int main(void)
{
    size_t *result = (size_t*)malloc(sizeof(size_t));
    size_t                           buffer_size = 0;
    int                       serialization_size = 0;
    COMPONENT_DATA                    *c_info = NULL; 
    COMPONENT_DATA       *c_info_deserialized = NULL;
    void*                serialization_buffer = NULL;
    int                        continuation_flag = 1;

    c_info = (COMPONENT_DATA*)malloc(sizeof(COMPONENT_DATA));
    c_info_deserialized = (COMPONENT_DATA*)malloc(sizeof(COMPONENT_DATA));
    
    if (NULL == c_info || NULL == c_info_deserialized)
    {
        fprintf(stderr,"Error when allocating memory for the struct(s).\n");
        continuation_flag = 0;
    }
    else
    {
        printf("Please give the buffer size.\n");
        
        if (0 == scanf("%zu",&buffer_size))
        {
            fprintf(stderr,"Failed to read buffer size.\n");
            continuation_flag = 0;
        }
        else
        {
            serialization_buffer = (void*)malloc(buffer_size);

            if (NULL == serialization_buffer)
            {
                fprintf(stderr,"Error when allocating buffer.\n");
                continuation_flag = 0;
            }

        }
        
    }

    if (1 == continuation_flag)
    {
        printf("Give the value of 'attributes' : ");
        
        if (0 == scanf("%d",&c_info->attributes))
        {
            fprintf(stderr,"Error when reading 'attributes'.\n");
            continuation_flag = 0;
        }
        else
        {
            printf("What is the name size?");
            
            if (0 == scanf("%zu",&c_info->nameSize))
            {
                fprintf(stderr,"Error when reading name size.\n");
                continuation_flag = 0;
            }
            else
            {
                c_info->name = (char*)malloc(c_info->nameSize);
                c_info_deserialized->name = (char*)malloc(c_info->nameSize);
                
                if( NULL == c_info->name || NULL == c_info_deserialized->name)
                {
                    fprintf(stderr,"Error when allocating memory to the 'name' field of struct.\n");
                    continuation_flag =0;
                }
                else
                {
                    getchar();

                    printf("Please input the name: ");
                    
                    if (NULL == fgets(c_info->name,c_info->nameSize,stdin))
                    {
                        fprintf(stderr,"Failed to read 'name'\n");
                        continuation_flag = 0;
                    }
                    else
                    {
                        
                        if ('\n' == c_info->name[strlen(c_info->name)-1])
                        {
                            c_info->name[strlen(c_info->name)-1]='\0';
                        }

                    }
                    
                }
                
            }
            
        }

    }

    if (1 == continuation_flag)
    {
        serialization_size = serialize_data(c_info,serialization_buffer,buffer_size,result);

        if (0 == *result && serialization_size < buffer_size)
        {
            serialization_size = deserialize_data(serialization_buffer,buffer_size,c_info_deserialized,result);
        }
        else
        {

            DBG_PRINT(1,"Error when serializing. Result: %zu\n",*result);
            if (serialization_size >= buffer_size)
            {
                DBG_PRINT(1,"Serialized data has %d bytes which can't fit in the buffer (given buffer size is %zu).\n",serialization_size,buffer_size);
            }
        }

        if (0 == *result)
        {
            /* a macro to clear the terminal before outputing */
            clearScreen();
            DBG_PRINT(5,"\nDeserialized data:\nSerialization size: %d \nAttributes:%d\nName:%s\nnameSize:%zu\n",serialization_size,c_info_deserialized->attributes,c_info_deserialized->name,c_info_deserialized->nameSize);
        }
        else
        {
            DBG_PRINT(1,"Error when deserializing. Result: %zu\n",*result);
        }

        free(result);
        free(serialization_buffer);
        free(c_info->name);
        free(c_info_deserialized->name);
        free(c_info);
        free(c_info_deserialized);
        result=0;
        serialization_buffer=0;
        c_info->name=NULL;
        c_info_deserialized->name=NULL;
        c_info=NULL;
        c_info_deserialized=NULL;
    }
      
    return 0;
}