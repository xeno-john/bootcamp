#include "p5.h"


int serializeData(COMPONENT_DATA* componentInfo, void* buffer, size_t bufferSize, size_t *result)
{
    int ret = 0;
    if(strlen(componentInfo->name)<bufferSize)
    {
        memcpy((int*)buffer,&componentInfo->attributes,sizeof(componentInfo->attributes));    
        memcpy((size_t*)buffer+sizeof(componentInfo->attributes),&componentInfo->nameSize,sizeof(componentInfo->nameSize));    
        strncpy((char*)buffer+sizeof(componentInfo->attributes)+sizeof(componentInfo->attributes),componentInfo->name,componentInfo->nameSize);   
        ret = sizeof(componentInfo->attributes)+sizeof(componentInfo->nameSize)+componentInfo->nameSize;
        *result=0;
    }
    else
    {
        ret = -1;
        *result=-1;
    }
    return ret;
}

int deserializeData(void *buffer, size_t bufferSize, COMPONENT_DATA* componentInfo, size_t *result)
{
    int ret = 0;
    if(*result==0)
    {
        memcpy(&(componentInfo->attributes),(int*)buffer,sizeof(componentInfo->attributes));    
        memcpy(&(componentInfo->nameSize),(size_t*)buffer+sizeof(componentInfo->attributes),sizeof(componentInfo->nameSize));    
        strncpy(componentInfo->name,(char*)buffer+sizeof(componentInfo->attributes)+sizeof(componentInfo->attributes),componentInfo->nameSize);
        ret = sizeof(componentInfo->attributes)+sizeof(componentInfo->nameSize)+componentInfo->nameSize;
        *result=0;
    }
    else
    {
        *result=-1;
    }
    return ret;
}

