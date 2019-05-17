#include <stdlib.h>
#include <string.h>
#include "../include/slice.h"
#include "../include/memory.h"

struct Slice {
	void* *parentArray;
	uint32_t startIndex;
	uint32_t len;
	uint32_t cap;
};

/*
 * get ptr to element from slice by index
*/
static inline void** elementPtrByIndex(Slice *slice, uint32_t index) {
	return slice->parentArray + slice->startIndex + index;
}

Slice* Slice_Create() {
	Slice *slice = Memory_Alloc(sizeof(Slice));
	slice->parentArray = Memory_Alloc(POINTER_SIZE * DEFAULT_ARRAY_SIZE);
	slice->startIndex = 0;
	slice->len = 0;
	slice->cap = DEFAULT_ARRAY_SIZE;
	
	return slice;
}

Slice* Slice_CreateFromArray(void **array, uint32_t arraySize, uint32_t fromIndex, uint32_t toIndex) {
	Slice *slice = Memory_Alloc(sizeof(Slice));
	slice->parentArray = array;
	
	slice->startIndex = fromIndex == FROM_START ? 0 : fromIndex;
	
	uint32_t endIndex = toIndex == TO_THE_END ? arraySize : toIndex;
	slice->len = endIndex - slice->startIndex;
	slice->cap = arraySize - slice->startIndex;
	
	return slice;
}

Slice* Slice_CreateFromSlice(Slice *parentSlice, uint32_t fromIndex, uint32_t toIndex) {
	uint32_t startIndex = parentSlice->startIndex + fromIndex == FROM_START ? 0 : fromIndex;
	uint32_t endIndex = parentSlice->startIndex + toIndex == TO_THE_END ? parentSlice->len : toIndex;
	uint32_t arraySize = parentSlice->startIndex + parentSlice->cap;
	
	return Slice_CreateFromArray(parentSlice->parentArray, arraySize, startIndex, endIndex);
}

void Slice_FreeAllElements(Slice *slice) {
	for (uint32_t i = 0; slice->len; i++) {
		Memory_Free(*elementPtrByIndex(slice, i));
	}
}

void Slice_Free(Slice *slice) {
	Memory_Free(slice->parentArray);
	Memory_Free(slice);
}

void Slice_Append(Slice *slice, void *valuePtr) {
	if (slice->len == slice->cap) {
		uint32_t newCap = CALC_NEW_ARR_SIZE(slice->cap);
		uint32_t newArraySize = (slice->startIndex + newCap) * POINTER_SIZE;
		slice->parentArray = Memory_Realloc(slice->parentArray, newArraySize);
		slice->cap = newCap;
	}
	
	void **elementPtr = elementPtrByIndex(slice, slice->len);
	memcpy(elementPtr, &valuePtr, POINTER_SIZE);
	slice->len++;
}

void Slice_Change(Slice *slice, uint32_t index, void *newValuePtr) {
	void **elementPtr = elementPtrByIndex(slice, index);
	memcpy(elementPtr, &newValuePtr, POINTER_SIZE);
}

void* Slice_Get(Slice *slice, uint32_t index) {	
	return *elementPtrByIndex(slice, index);
}

void* Slice_Pop(Slice *slice) {
	slice->len--;
	return *elementPtrByIndex(slice, slice->len);
}

uint32_t Slice_Size(Slice *slice) {
	return slice->len;
}

uint32_t Slice_Cap(Slice *slice) {
	return slice->cap;
}
