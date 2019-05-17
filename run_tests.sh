#! /bin/sh

. ./build.sh

cd testing_lib &&
. ./build.sh

TESTS_DIR="tests"

cd .. &&
cc \
	-Wall -pedantic \
       	"$TESTS_DIR/main.c" "$TESTS_DIR/list_test.c" "testing_lib/check.o" \
	-L$BUILD_DIR -l$LIB_NAME \
	-o "$BUILD_DIR/tests.out" &&
./$BUILD_DIR/tests.out
