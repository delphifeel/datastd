#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_ARRAY_SIZE (10)
#define POINTER_SIZE       (sizeof(void*))

#define CALC_NEW_ARR_SIZE(_OLD_SIZE) (_OLD_SIZE * 2 + 1)

typedef int32_t (*ParseElementValueFunc)(void *elementPtr);

int32_t* createIntPtr(int32_t value);
void* Memory_Alloc(size_t size);
void* Memory_Realloc(void* ptr, size_t newSize);
void Memory_Free(void* ptr);

#endif
