#include <string.h>
#include "../testing_lib/check.h"
#include "../include/str_holder.h"
#include "../include/memory.h"

void check_StrHolder_Add() {
	char *test_strings[] = {
		"Hello, ",
		"World.",
		"\r\nOr wait...",
	};

	StrHolder *strHolder = StrHolder_Create();
	
	StrHolder_Add(strHolder, test_strings[0]);
	StrHolder_Add(strHolder, test_strings[1]);
	char *str = StrHolder_GetString(strHolder);

	char conc_strings[256] = {0};
	strcat(conc_strings, test_strings[0]);
	strcat(conc_strings, test_strings[1]);

	check("concatenate 2 strings", strcmp(str, conc_strings) == 0);

	StrHolder_Add(strHolder, test_strings[2]);
	char *str_ex = StrHolder_GetString(strHolder);

	strcat(conc_strings, test_strings[2]);

	check("... and one more", strcmp(str_ex, conc_strings) == 0);
	
	StrHolder_Free(strHolder, true);
}

void str_holder_test() {
	check_method("StrHolder_Add", check_StrHolder_Add);	
}

CREATE_TEST(str_holder_test)

