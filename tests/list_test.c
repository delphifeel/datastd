#include <stddef.h>
#include "../testing_lib/check.h"
#include "../include/list.h"
#include "../include/memory.h"
#include "../include/iterator.h"

void check_List_Create() {
	List *list = List_Create();

	check("list != NULL",		list != NULL);	
	check("list->head == NULL", 	list->head == NULL);	
	check("list->tail == NULL", 	list->tail == NULL);	

	List_Free(list, false);
}

void check_List_Append() {
	List *list = List_Create();

	// if first node - head and tail the same
	int first_value = 333;
	List_Append(list, &first_value);

	check("if first node - head == tail", list->head == list->tail);

	// if second node - head old, tail is new 
	int second_value = 666;
	List_Append(list, &second_value);

	check("if second node - head same, tail changes", 
			(list->head != list->tail) &&
			(list->head->value == &first_value) &&
			(list->tail->value == &second_value));

	// if third node and so on - same behavior as with second node
	int third_value = 999;
	List_Append(list, &third_value);

	check("if third node and so on - head same, tail changes", 
			(list->head != list->tail) &&
			(list->head->value == &first_value) &&
			(list->tail->value == &third_value));

	List_Free(list, false);
}

void check_List_Prepend() {
	List *list = List_Create();

	// if first node - head and tail the same
	int first_value = 444;
	List_Prepend(list, &first_value);

	check("if first node - head == tail", list->head == list->tail);

	// if second node - head new, tail old 
	int second_value = 777;
	List_Prepend(list, &second_value);

	check("if second node - head same, tail changes", 
			(list->head != list->tail) &&
			(list->head->value == &second_value) &&
			(list->tail->value == &first_value));

	// if third node and so on - same behavior as with second node
	int third_value = 978;
	List_Prepend(list, &third_value);

	check("if third node and so on - head same, tail changes", 
			(list->head != list->tail) &&
			(list->head->value == &third_value) &&
			(list->tail->value == &first_value));

	List_Free(list, false);
}

void check_List_Empty() {
	List *list = List_Create();

	// if head is NULL and tail is NULL - list is empty
	check("if head is NULL and tail is NULL - list is empty", 
			List_Empty(list) == true);
	
	// if head is NULL and tail is NOT NULL - list is NOT empty
	int pseudo_tail_node_value = -333;
	ListNode *pseudo_tail_node = Memory_Alloc(sizeof(ListNode));
	pseudo_tail_node->value = &pseudo_tail_node_value;
	pseudo_tail_node->next = NULL;

	list->tail = pseudo_tail_node; 

	check("if head is NULL and tail is NOT NULL - list is NOT empty", 
			List_Empty(list) == false);
	
	Memory_Free(list->tail);
	list->tail = NULL;

	// if head is NOT NULL and tail is NULL - list is NOT empty
	int pseudo_head_node_value = -898;
	ListNode *pseudo_head_node = Memory_Alloc(sizeof(ListNode));
	pseudo_head_node->value = &pseudo_head_node_value;
	pseudo_head_node->next = NULL;
	
	list->head = pseudo_head_node; 

	check("if head is NOT NULL and tail is NULL - list is NOT empty", 
			List_Empty(list) == false);

	Memory_Free(list->head);
	list->head = NULL;

	List_Free(list, false);
}

void check_ListIteration() {
	int *value_ptr;
	int first  = 10;
	int second = 33;
	int third  = 99;

	List *list = List_Create();

	List_Append(list, &first);
	List_Append(list, &second);
	List_Append(list, &third);

	Iterator *iter = CREATE_ITERATOR(List);
	
	value_ptr = iter->next(iter, list);
	check("first value correct", value_ptr == &first);

	value_ptr = iter->next(iter, list);
	check("second value correct", value_ptr == &second);

	value_ptr = iter->next(iter, list);
	check("third value correct", value_ptr == &third);

	value_ptr = iter->next(iter, list);
	check("no value after third", value_ptr == NULL);

	FREE_ITERATOR(List, iter);

	List_Free(list, false);
}

void list_test() {
	check_method("List_Create", check_List_Create);
	check_method("List_Append", check_List_Append);
	check_method("List_Prepend", check_List_Prepend);
	check_method("List_Empty", check_List_Empty);
	check_method("List iteration", check_ListIteration);
}

CREATE_TEST(list_test)
