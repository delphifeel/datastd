#include <stdio.h>

char *__checkStatus;

void check_method(char *name, void (*func)()) {
	printf("\t| %s\n", name);
	func();
}

void check(char *text, int result) {
	__checkStatus = result ? "   Good" : "* ERROR";
	printf("\t\t%s: %s\n", __checkStatus, text);
}

