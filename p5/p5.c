#include "p5.h"
#include<stdlib.h>

int main(int argc, char* argv[])
{
    size_t *result = (size_t*)malloc(sizeof(size_t));
    size_t bufferSize = 0;
    int serializationSize = 0;
    COMPONENT_DATA *cInfo=0, *cInfoDeserialized = 0;
    void* buffer = 0;

    // allocating memory for the struct that is going to be
    // serialized and the one that is going to be deserialized
    cInfo = (COMPONENT_DATA*)malloc(sizeof(COMPONENT_DATA));
    cInfoDeserialized = (COMPONENT_DATA*)malloc(sizeof(COMPONENT_DATA));
    // classic verification if everything went ok
    if(cInfo == 0)
    {
        fprintf(stderr,"Error when allocating memory for the struct.\n");
        exit(EXIT_FAILURE);
    }

    printf("Please give the buffer size.\n");
    scanf("%zu",&bufferSize);
    
    //allocating memory for the void buffer (where we are
    //going to copy the data from the struct)
    buffer = (void*)malloc(bufferSize);
    if(buffer == 0)
    {
        fprintf(stderr,"Error when allocating buffer.\n");
        exit(EXIT_FAILURE);
    }

    printf("Give the value of 'attributes' : ");
    scanf("%d",&cInfo->attributes);

    printf("What is the name size?");
    scanf("%zu",&cInfo->nameSize);

    //allocating memory for the string in the struct(s).
    cInfo->name = (char*)malloc(cInfo->nameSize);
    cInfoDeserialized->name = (char*)malloc(cInfo->nameSize);
    if(cInfo->name == 0)
    {
        fprintf(stderr,"Error when allocating memory for the name in the struct.\n");
        exit(EXIT_FAILURE);
    }
    //getchar() to clear the stdin buffer.
    getchar();
    //reading the name in the struct from stdin
    printf("Please input the name: ");
    fgets(cInfo->name,cInfo->nameSize,stdin);

    //we get rid of the potential \n read at the end of the string
    if(cInfo->name[strlen(cInfo->name)-1]=='\n')
    {
        cInfo->name[strlen(cInfo->name)-1]='\0';
    }

    //here we call the function that serializes the data.
    //it will return the size in bytes of the serialized data
    //result will say if everything went ok
    //we will have our values stocked in the 'buffer' value
    serializationSize = serializeData(cInfo,buffer,bufferSize,result);
    //IF everything went OK
    //AND the data we serialized is SMALLER in sizethan the buffer
    if(*result==0 && serializationSize < bufferSize)
    {
        //we move further do deserializing the data
        serializationSize = deserializeData(buffer,bufferSize,cInfoDeserialized,result);
    }
    else
    {
        //otherwise we indicate where the error came from.
        DBG_PRINT(1,"Error when serializing. Result: %zu\n",*result);
        if(serializationSize >= bufferSize)
        {
            //and if it was related to the size of the serialized data.
            DBG_PRINT(1,"Serialized data has %d bytes which can't fit in the buffer (given buffer size is %zu).\n",serializationSize,bufferSize);
        }
        //terminate execution, no point in going further
        exit(EXIT_FAILURE);
    }
    //if we get the ok flag from the deserialization function
    if(*result==0)
    {
        //a macro to clear the terminal before outputing
        clearScreen();
        //we print the that we've deserialized.
        DBG_PRINT(5,"\nDeserialized data:\nSerialization size: %d \nAttributes:%d\nName:%s\nnameSize:%zu\n",serializationSize,cInfoDeserialized->attributes,cInfoDeserialized->name,cInfoDeserialized->nameSize);
    }
    else
    {
        //otherwise, we indicate where the error is coming from
        DBG_PRINT(1,"Error when deserializing. Result: %zu\n",*result);
        //and terminate the execution
        exit(EXIT_FAILURE);
    }

    //freeing the memory we occupied
    free(result);
    free(buffer);
    free(cInfo->name);
    free(cInfoDeserialized->name);
    free(cInfo);
    free(cInfoDeserialized);
    result=0;
    buffer=0;
    cInfo->name=0;
    cInfoDeserialized->name=0;
    cInfo=0;
    cInfoDeserialized=0;
      
    return 0;
}
