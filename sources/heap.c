#include <stdint.h>
#include <stddef.h>
#include "../include/memory.h"
#include "../include/slice.h"
#include "../include/heap.h"

struct MaxHeap {
	Slice *dataSlice;
	ParseElementValueFunc ParseElementValue;
};

#define PARSE_VALUE_FROM_HEAP(_HEAP, _INDEX) \
	_HEAP->ParseElementValue(Slice_Get(_HEAP->dataSlice, _INDEX)) \

static inline void swap(Slice *slice, uint32_t leftIndex, uint32_t rightIndex) {
	if (leftIndex == rightIndex) {
		return;
	}
	
	void *left = Slice_Get(slice, leftIndex);
	void *right = Slice_Get(slice, rightIndex);
	
	Slice_Change(slice, leftIndex, right);
	Slice_Change(slice, rightIndex, left);
}	

static void heapify(Slice *slice, ParseElementValueFunc parseValue, uint32_t index) {
	#define VALUE_BY_INDEX(_INDEX) parseValue(Slice_Get(slice, _INDEX))
	
	int32_t tmpValue;
	uint32_t size = Slice_Size(slice);
	if (size == 0) {
		return;
	}
	
	while (1) {	
		uint32_t largest = index;
		int32_t largest_value = VALUE_BY_INDEX(largest);
		uint32_t left = largest * 2 + 1;
		uint32_t right = left + 1;
	
		if ((left < size) && ((tmpValue = VALUE_BY_INDEX(left)) > largest_value)) {
			largest = left;
			largest_value = tmpValue;
		}
	
		if ((right < size) && (VALUE_BY_INDEX(right) > largest_value)) {
			largest = right;
		}
	
		if (largest == index) {
			break;
		}
		
		swap(slice, index, largest);
		index = largest;
	}
}

MaxHeap* MaxHeap_Create(ParseElementValueFunc parseElementValueFunc) {
	MaxHeap *heap = Memory_Alloc(sizeof(MaxHeap));
	heap->dataSlice = Slice_Create();
	heap->ParseElementValue = parseElementValueFunc;
	
	return heap;
}

MaxHeap* MaxHeap_CreateFromArray(uint32_t array_size, void* array[array_size], ParseElementValueFunc parseElementValueFunc) {
	Slice *slice = Slice_CreateFromArray(array, array_size, FROM_START, TO_THE_END);
	for (int32_t i = Slice_Size(slice) / 2 - 1; i >= 0; i--) {
		heapify(slice, parseElementValueFunc, i);
	}
	
	MaxHeap *heap = Memory_Alloc(sizeof(MaxHeap));
	heap->dataSlice = slice;
	heap->ParseElementValue = parseElementValueFunc;
	
	return heap;
}

void MaxHeap_Free(MaxHeap *heap) {
	Slice_Free(heap->dataSlice);
	Memory_Free(heap);
}

void MaxHeap_FreeAllElements(MaxHeap *heap) {
	Slice_FreeAllElements(heap->dataSlice);
}

void MaxHeap_Add(MaxHeap *heap, void *value) {
	// insert node so a heap is completed binary tree
	Slice_Append(heap->dataSlice, value);
	
	uint32_t childIndex = Slice_Size(heap->dataSlice) - 1;
	
	while (childIndex > 0) {
		uint32_t parentIndex = (childIndex - 1) / 2;
		
		int32_t childValue = PARSE_VALUE_FROM_HEAP(heap, childIndex);
		int32_t parentValue = PARSE_VALUE_FROM_HEAP(heap, parentIndex);
		if (childValue < parentValue) {
			break;
		}
		
		swap(heap->dataSlice, childIndex, parentIndex);
		
		childIndex = parentIndex;
	}
}

void* MaxHeap_Pop(MaxHeap *heap) {
	uint32_t nodesCount = Slice_Size(heap->dataSlice);
	if (nodesCount == 0) {
		return NULL;
	}
	
	// swap root with last node and remove last node
	swap(heap->dataSlice, 0, nodesCount - 1);
	
	void *result = Slice_Pop(heap->dataSlice);
	
	heapify(heap->dataSlice, heap->ParseElementValue, 0);
	
	return result;
}
