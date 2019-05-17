#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include "list.h"
#include "iterator.h"

/* 
 * type Map - structure that contain array of Buckets.
 * type Bucket - List of BucketNodes.
 */

typedef struct Map {
	/* @buckets - array of Buckets */
	List*	*buckets;
	
	/* @buckets_count - size of @buckets array */
	size_t	buckets_count;
} Map;

typedef struct BucketNode {
	const char	*key;
	size_t		key_size;
	void		*value;
} BucketNode;

Map* Map_Create(size_t map_size);
void Map_Free(Map *map);
void Map_Set(Map *map, const char *key, size_t key_size, void *value);
void* Map_Get(Map *map, const char *key, size_t key_size);
void Map_Change(Map *map, const char *key, size_t key_size, void *value);

ITERATOR_INTERFACE(Map)

#endif

