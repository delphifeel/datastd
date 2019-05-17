#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct Iterator {
	void*	__state;

	void*	(*next)	(struct Iterator *iterator, void* source);
} Iterator;

#define __ITER_CONSTRUCTOR_NAME(_TYPE) __createIteratorFor ## _TYPE

#define __ITER_DESTRUCTOR_NAME(_TYPE) __freeIteratorFor ## _TYPE

#define __ITER_CONSTRUCTOR_HEADER(_TYPE) \
	Iterator* __ITER_CONSTRUCTOR_NAME(_TYPE)() \

#define __ITER_DESTRUCTOR_HEADER(_TYPE) \
	void __ITER_DESTRUCTOR_NAME(_TYPE)(Iterator *iterator) \

#define ITERATOR_INTERFACE(_TYPE) \
	__ITER_CONSTRUCTOR_HEADER(_TYPE); \
	__ITER_DESTRUCTOR_HEADER(_TYPE); \

#define EXTERN_ITERATOR_CONSTRUCTOR(_TYPE, _FUNC) \
	__ITER_CONSTRUCTOR_HEADER(_TYPE) { \
		return _FUNC(); \
	} \

#define EXTERN_ITERATOR_DESTRUCTOR(_TYPE, _FUNC) \
	__ITER_DESTRUCTOR_HEADER(_TYPE) { \
		_FUNC(iterator); \
	} \

#define CREATE_ITERATOR(_TYPE) \
	__ITER_CONSTRUCTOR_NAME(_TYPE)();

#define FREE_ITERATOR(_TYPE, _ITERATOR) \
	__ITER_DESTRUCTOR_NAME(_TYPE)(_ITERATOR);

#endif

