#include "../testing_lib/check.h"
#include "../include/slice.h"

void check_Slice_Append() {
	Slice *slice = Slice_Create();
	
	char *str1 = "Hello, ";
	char *str2 = "World.";

	Slice_Append(slice, str1);
	Slice_Append(slice, str2);

	check("adding 2 strings works correctly.", (Slice_Get(slice, 0) == str1) &&
						   (Slice_Get(slice, 1) == str2));

	Slice_Free(slice);

	slice = Slice_Create();

	char *loop_str = "THIS WILL BE LOOPED...";
	for (int i = 0; i < 100; i++) {
		Slice_Append(slice, loop_str);
	}

	int result = 1;

	for (int i = 0; i < 100; i++) {
		result = result && Slice_Get(slice, i) == loop_str;
	}

	check("adding string 100 times works correctly", result);

	Slice_Free(slice);
}

void slice_test() {
	check_method("Slice_Append", check_Slice_Append);
}

CREATE_TEST(slice_test)

