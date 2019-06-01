#include <stddef.h>
#include <string.h>
#include "../include/str_holder.h"
#include "../include/memory.h"

#define BUFFER_SIZE (256)

StrHolder* StrHolder_Create() {
	StrHolder *strHolder = Memory_Alloc(sizeof(StrHolder));
	strHolder->src = Memory_Alloc(BUFFER_SIZE * sizeof(char));
	strHolder->size = 0;
	strHolder->max_size = BUFFER_SIZE;

	return strHolder;
}

void StrHolder_Free(StrHolder *strHolder, bool freeString) {
	if (freeString == true) {
		Memory_Free(strHolder->src);
	}

	Memory_Free(strHolder);
}

void StrHolder_Add(StrHolder *strHolder, const char *value) {
	const char *iter = value;
	while (1) {
		if (strHolder->size == strHolder->max_size) {
			strHolder->max_size *= 2;
			strHolder->src = Memory_Realloc(strHolder->src, 
							 strHolder->max_size);
		}
		
		strHolder->src[strHolder->size] = *iter;
		
		if (*iter == '\0') {
			break;
		}

		strHolder->size++;
		
		iter++;
	}
}

char* StrHolder_GetString(StrHolder *strHolder) {
	return strHolder->src;
}

uint32_t StrHolder_Size(StrHolder *strHolder) {
	return strHolder->size;
}

