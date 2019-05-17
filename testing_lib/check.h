#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>

#define __TEST_NAME(_FUNC) __checkTest__ ## _FUNC

#define __TEST_HEADER(_FUNC) \
	void __TEST_NAME(_FUNC)() \

#define CREATE_TEST(_FUNC) \
	__TEST_HEADER(_FUNC) { \
		_FUNC(); \
	} \

#define CHECK_TEST(_NAME) \
	printf("TEST: %s\n", #_NAME); \
	__TEST_HEADER(_NAME); \
	__TEST_NAME(_NAME)(); \

char *__checkStatus;

void check_method(char *name, void (*func)());
void check(char *text, int result);

#endif

