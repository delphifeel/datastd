#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>

#define POINTER_SIZE       (sizeof(void*))

typedef int32_t (*ParseElementValueFunc)(void *elementPtr);

int32_t* createIntPtr(int32_t value);
void* Memory_Alloc(size_t size);
void* Memory_Realloc(void* ptr, size_t newSize);
void Memory_Free(void* ptr);

#endif
