#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stdbool.h>
#include "iterator.h"

typedef struct ListNode {
	void 		*value;
	struct ListNode *next;
} ListNode;


typedef struct List {
	ListNode *head;
	ListNode *tail;
} List;

List* List_Create();
void List_Free(List *list, bool freeValues);
void List_Append(List *list, void *value);
void List_Prepend(List *list, void *value);
bool List_Empty(List *list);

ITERATOR_INTERFACE(List)

#endif
