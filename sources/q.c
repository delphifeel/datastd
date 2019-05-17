#include <stdbool.h>
#include <stddef.h>
#include "../include/memory.h"
#include "../include/q.h"

Q* Q_Create() {
	Q *q = Memory_Alloc(sizeof(Q));
	q->dataList = List_Create();
	
	return q;
}

bool Q_Empty(Q *q) {
	return List_Empty(q->dataList);
}

void Q_Free(Q *q, bool freeValues) {
	List_Free(q->dataList, freeValues);
	Memory_Free(q);
}

void Q_Enq(Q *q, void *value) {
	List_Append(q->dataList, value);
} 

void* Q_Deq(Q *q) {
	List *list = q->dataList;
	if (list->head == NULL) {
		return NULL;
	}
	
	if (list->head == list->tail) {
		list->tail = NULL;
	}
	
	void *oldValue = list->head->value;
	list->head = list->head->next;
	
	return oldValue;
}
