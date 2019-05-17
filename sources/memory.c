#include <stdlib.h>
#include <stdint.h>
#include "../include/memory.h"

int32_t* createIntPtr(int32_t value) {
	int32_t *ptr = malloc(sizeof(int32_t));
	*ptr = value;
	return ptr;
}

void* Memory_Alloc(size_t size) {
	return malloc(size);
}

void* Memory_Realloc(void* ptr, size_t newSize) {
	return realloc(ptr, newSize);
}

void Memory_Free(void* ptr) {
	free(ptr);
}
