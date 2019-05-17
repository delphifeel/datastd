#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stdbool.h>
#include "slice.h"
#include "memory.h"

typedef struct MaxHeap MaxHeap;

MaxHeap* MaxHeap_Create(ParseElementValueFunc parseElementValueFunc);
MaxHeap* MaxHeap_CreateFromArray(uint32_t array_size, void* array[array_size], ParseElementValueFunc parseElementValueFunc);
void MaxHeap_Free(MaxHeap *heap);
void MaxHeap_FreeAllElements(MaxHeap *heap);
void MaxHeap_Add(MaxHeap *heap, void *value);
void* MaxHeap_Pop(MaxHeap *heap);

#endif