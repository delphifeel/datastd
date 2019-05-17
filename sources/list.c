#include <stdbool.h>
#include <stddef.h>
#include "../include/list.h"
#include "../include/memory.h"

static ListNode* ListNode_Create(void *value) {
	ListNode *node = Memory_Alloc(sizeof(ListNode));
	node->value = value;
	node->next = NULL;
	
	return node;
}

List* List_Create() {
	List *list = Memory_Alloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	
	return list;
}

void List_Free(List *list, bool freeValues) {
	ListNode *iter = list->head;
	while (iter != NULL) {
		ListNode *elementToFree = iter;
		iter = iter->next;
		if (freeValues) {
			Memory_Free(elementToFree->value);
		}
		Memory_Free(elementToFree);
	}
	
	Memory_Free(list);
}

void List_Append(List *list, void *value) {
	ListNode *new_node = ListNode_Create(value);
	if (list->head == NULL) {
		list->head = new_node;
	}
	
	if (list->tail != NULL) {
		list->tail->next = new_node;
	}
	
	list->tail = new_node;
}

void List_Prepend(List *list, void *value) {
	ListNode *new_node = ListNode_Create(value);
	if (list->head != NULL) {
		new_node->next = list->head;
	}
	
	list->head = new_node;
	
	if (list->tail == NULL) {
		list->tail = new_node;
	}
}

bool List_Empty(List *list) {
	return (list->head == NULL) && (list->tail == NULL);
}

static int state_empty_value = -1;
static int *const state_empty_handler = &state_empty_value;

static void* nextIteration(Iterator *iterator, void* source) {
	List *list = source;
	if (iterator->__state == state_empty_handler) {
		iterator->__state = list->head;
	}

	ListNode *listNode = iterator->__state;
	
	if (listNode == NULL) {
		return NULL;
	}
	void* result = listNode->value;
	iterator->__state = listNode->next;
	return result;
}

static Iterator* createIterator() {
	Iterator *iterator = Memory_Alloc(sizeof(Iterator));
	iterator->__state = state_empty_handler;
	iterator->next = nextIteration;

	return iterator;
}

static void freeIterator(Iterator *iterator) {
	Memory_Free(iterator);
}

EXTERN_ITERATOR_CONSTRUCTOR(List, createIterator)

EXTERN_ITERATOR_DESTRUCTOR(List, freeIterator)

