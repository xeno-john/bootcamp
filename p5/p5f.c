#include "p5.h"

/**
 *  @brief Function that receives data, serializes it, and returns the serialized size in bytes.
 *  @param [in] component_info - pointer to the struct that will be serialized
 *  @param [in] serialization_buffer - void ptr in which we will stock the data
 *  @param [in] buffer_size - size of the buffer
 *  @param [in/out] result - pointer which will have the value at that address 0 if everything went ok, -1 otherwise
 *  @return int serialization_size - will be -1 if something goes wrong, and the size in bytes of serialized data if everything goes accordingly
 */
int serialize_data(COMPONENT_DATA* component_info, void* serialization_buffer, size_t buffer_size, size_t *result)
{
    int serialization_size = 0; 

    if ((strlen(component_info->name)<buffer_size) && (NULL != component_info) && (NULL != serialization_buffer)) /* if the data we have as input fits in the buffer  */ 
    {
        memcpy((int*)serialization_buffer,&component_info->attributes,sizeof(component_info->attributes)); 
        memcpy((size_t*)serialization_buffer+sizeof(component_info->attributes),&component_info->nameSize,sizeof(component_info->nameSize)); 
        memcpy((char*)serialization_buffer+sizeof(component_info->attributes)+sizeof(component_info->attributes),component_info->name,component_info->nameSize);   
        serialization_size = sizeof(component_info->attributes)+sizeof(component_info->nameSize)+component_info->nameSize;
        *result=0;
    }
    else
    {
        serialization_size = -1;
        *result=-1;
    }

    return serialization_size;
}

/**
 *  @brief Function that receives serialized data, deserializes it, and returns the deserialized size in bytes.
 *  @param [in] serialization_buffer - void ptr in which we have the serialized data stocked
 *  @param [in] buffer_size - size of the buffer
 *  @param [in] component_info - pointer to the struct that will be populated with the data found in serialization_buffer
 *  @param [in/out] result - pointer which will have the value at that address 0 if everything went ok, -1 otherwise
 *  @return int deserialized_size - will be -1 if something goes wrong, and the size in bytes of deserialized data if everything goes accordingly
 */
int deserialize_data(void *serialization_buffer, size_t buffer_size, COMPONENT_DATA* component_info, size_t *result)
{
    int deserialized_size = 0;
    if ((*result==0) && (NULL != serialization_buffer) && (NULL != component_info))
    {
        memcpy(&(component_info->attributes),(int*)serialization_buffer,sizeof(component_info->attributes));    
        memcpy(&(component_info->nameSize),(size_t*)serialization_buffer+sizeof(component_info->attributes),sizeof(component_info->nameSize));    
        memcpy(component_info->name,(char*)serialization_buffer+sizeof(component_info->attributes)+sizeof(component_info->attributes),component_info->nameSize);
        deserialized_size = sizeof(component_info->attributes)+sizeof(component_info->nameSize)+component_info->nameSize;
        *result=0;
    }
    else
    {
        *result=-1;
        deserialized_size = -1;
    }

    return deserialized_size;
}

