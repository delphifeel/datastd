#!/bin/sh

FILES="heap list map memory q slice str_holder"
SRC_DIR="sources"
BUILD_DIR="build"
INCLUDE_DIR="include"
OBJECTS_DIR="$BUILD_DIR/objects"
LIB_NAME="datastd"
LIB_FILE_NAME="lib$LIB_NAME.a"

IS_DEV="false"
FORCE_RECOMPILE="false"
COMPILE_OPTIONS=""

usage()
{
	echo "./build.sh [--force] [--dev]"
	echo "--force - force rebuild"
	echo "--dev - build with debug info"
}

for param in $@; do
	case $param in
		--dev)
			IS_DEV="true"
			;;
		--force)
			FORCE_RECOMPILE="true"
			;;
		--help)
			usage
			exit
			;;
	esac
done

if [ "$IS_DEV" = "true" ]; then
	COMPILE_OPTIONS="$COMPILE_OPTIONS -g"
else
	COMPILE_OPTIONS="$COMPILE_OPTIONS -O3"
fi

try_create_dir()
{
	if [ ! -d $1 ]; then
		mkdir $1
	fi
}

compile_c_file()
{
	local O_FILE="$OBJECTS_DIR/$1.o"
	local C_FILE="$SRC_DIR/$1.c"

	if [ ! -e $O_FILE ] || 
	   [ "$FORCE_RECOMPILE" = "true" ] ||
	   [ $C_FILE -nt $O_FILE ]; then
		cc $COMPILE_OPTIONS -Wall -c $C_FILE -o $O_FILE
	fi
}

create_static_lib()
{
	ar rcs "$BUILD_DIR/$LIB_FILE_NAME" $1
}


try_create_dir $BUILD_DIR
try_create_dir $OBJECTS_DIR

for NAME in $FILES; do
	compile_c_file $NAME
done

O_FILES=""
for NAME in $FILES; do
	O_FILES="$O_FILES $OBJECTS_DIR/$NAME.o";
done

create_static_lib "$O_FILES"
