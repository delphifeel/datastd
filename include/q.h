#ifndef Q_H
#define Q_H

#include "list.h"

typedef struct Q {
	List *dataList;
} Q;

Q* Q_Create();
bool Q_Empty(Q *q);
void Q_Enq(Q *q, void *value);
void* Q_Deq(Q *q);
void Q_Free(Q *q, bool freeValues);

#endif
