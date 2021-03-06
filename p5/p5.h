#ifndef P5_H_
#define P5_H_

#include "../DBG_PRINT.h"
#include <stdint.h>
#include <string.h>

typedef struct _COMPONENT_DATA
{
    int attributes;
    char *name;
    size_t nameSize;
} COMPONENT_DATA, *PCOMPONENT_DATA;

int serialize_data(COMPONENT_DATA* componentInfo, void* buffer, size_t bufferSIze, size_t *result);
int deserialize_data(void *buffer, size_t bufferSize, COMPONENT_DATA* componentInfo, size_t *result);

#endif
