#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>

#define DEFAULT_ARRAY_SIZE	(10)
#define FROM_START 		(0)
#define TO_THE_END 		(UINT32_MAX)

typedef struct Slice Slice;

Slice* Slice_Create();
Slice* Slice_CreateFromArray(void **array, uint32_t arraySize, uint32_t fromIndex, uint32_t toIndex);
Slice* Slice_CreateFromSlice(Slice *parentSlice, uint32_t fromIndex, uint32_t toIndex);
void Slice_Free(Slice *slice);
void Slice_FreeAllElements(Slice *slice);
void Slice_Append(Slice *slice, void *valuePtr);
void Slice_Change(Slice *slice, uint32_t index, void *newValuePtr);
void* Slice_Get(Slice *slice, uint32_t index);
void* Slice_Pop(Slice *slice);
uint32_t Slice_Size(Slice *slice);
uint32_t Slice_Cap(Slice *slice);

#endif
