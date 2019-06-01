#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"
#include "../include/memory.h"
#include "../include/super_fast_hash.h"
#include "../include/map.h"
#include "../include/iterator.h"

static BucketNode* createBucketNode(const char *key, size_t key_size, void *value) {
	BucketNode *bucketNode = Memory_Alloc(sizeof(BucketNode));
	bucketNode->key = key;
	bucketNode->key_size = key_size;
	bucketNode->value = value;

	return bucketNode;
}

static List* getBucketByKey(Map *map, const char *key, size_t key_size) {
	uint64_t hash = SuperFastHash(key, key_size);
	uint64_t bucket_index = hash % map->buckets_count; 
	return map->buckets[bucket_index];
}

Map* Map_Create(size_t map_size) {
	Map *map = Memory_Alloc(sizeof(Map));
	map->buckets = Memory_Alloc(sizeof(List*) * map_size);
	for (size_t i = 0; i < map_size; i++) {
		map->buckets[i] = List_Create();
	}
	map->buckets_count = map_size;

	return map;
}

void Map_Free(Map *map) {
	for (size_t i = 0; i < map->buckets_count; i++) {
		List *bucket = map->buckets[i];
		List_Free(bucket, true);
	}

	Memory_Free(map->buckets);
	Memory_Free(map);
}

void Map_Set(Map *map, const char *key, size_t key_size, void *value) {
	List *bucket = getBucketByKey(map, key, key_size);
	BucketNode *newBucketNode = createBucketNode(key, key_size, value);	

	List_Prepend(bucket, newBucketNode);
}

static BucketNode* findBucketNode(Map *map, const char *key, size_t key_size) {		
	BucketNode *result = NULL;
	List *bucket = getBucketByKey(map, key, key_size);

	Iterator *bucketIterator = CREATE_ITERATOR(List);
	BucketNode *bucketNode;

	while ((bucketNode = bucketIterator->next(bucketIterator, bucket))) {
		if (bucketNode->key_size == key_size) {
			int cmp_result = memcmp(bucketNode->key, key, key_size);
			if (cmp_result == 0) {
				result = bucketNode;
				break;
			}	
		}			
	}

	FREE_ITERATOR(List, bucketIterator);
	return result;
}

void* Map_Get(Map *map, const char *key, size_t key_size) {
	BucketNode *bucketNode = findBucketNode(map, key, key_size);
	return bucketNode == NULL ? NULL : bucketNode->value;
}

void Map_Change(Map *map, const char *key, size_t key_size, void *value) {	
	BucketNode *bucketNode = findBucketNode(map, key, key_size);
	if (bucketNode != NULL) {
		bucketNode->value = value;
	}
} 

typedef struct MapIteratorState {
	Iterator *bucketIterator;
	int 	 index;
} MapIteratorState;

static void prepareNextBucketIterator(Map *map, MapIteratorState *state, int startIndex) {
	List *bucket;

	do {
		if (startIndex == map->buckets_count) {
			if (state->bucketIterator != NULL)
				FREE_ITERATOR(List, state->bucketIterator);	
			state->bucketIterator = NULL;
			break;
		}
	
		bucket = map->buckets[startIndex];
		startIndex++;
	} while (List_Empty(bucket) == true);

	startIndex--;
	state->index = startIndex;
	if (state->bucketIterator != NULL) {
		FREE_ITERATOR(List, state->bucketIterator);	
	}
	state->bucketIterator = CREATE_ITERATOR(List);
}

static void* nextIter(Iterator *iterator, void* source) {
	Map *map = source;
	MapIteratorState *state = iterator->__state;
	if (state->bucketIterator == NULL) {
		prepareNextBucketIterator(map, state, 0);
	}

	Iterator *bucketIterator = state->bucketIterator;
	
	void* result = bucketIterator->next(bucketIterator, map->buckets[state->index]);
	
	/* if current bucket iteration finished and there are more buckets */
	if ((bucketIterator->__state == NULL) &&
	    (state->index < map->buckets_count - 1))
	{
		prepareNextBucketIterator(map, state, state->index + 1);
	}

	return result;
}

void freeIterator(Iterator *iterator) {
	MapIteratorState *state = iterator->__state;

	if (state->bucketIterator != NULL) {
		FREE_ITERATOR(List, state->bucketIterator);	
	}
	Memory_Free(state);	
	Memory_Free(iterator);
}

static Iterator* createIterator() {
	MapIteratorState *state = Memory_Alloc(sizeof(MapIteratorState));
	state->index = 0;
	state->bucketIterator = NULL;
	
	Iterator *iterator = Memory_Alloc(sizeof(Iterator));
	iterator->__state = state;
	iterator->next = nextIter;

	return iterator;
}

EXTERN_ITERATOR_CONSTRUCTOR(Map, createIterator)

EXTERN_ITERATOR_DESTRUCTOR(Map, freeIterator)
