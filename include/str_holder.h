#ifndef STR_HOLDER_H
#define STR_HOLDER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct StrHolder {
	char 		*src;
	uint32_t 	size;
	uint32_t	max_size;
} StrHolder;

StrHolder*	StrHolder_Create	();
void		StrHolder_Free		(StrHolder*, bool freeString);
void		StrHolder_Add		(StrHolder*, const char *value);
char*		StrHolder_GetString	(StrHolder*);
uint32_t	StrHolder_Size		(StrHolder*);

#endif

