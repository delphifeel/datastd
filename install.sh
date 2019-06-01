#! /bin/sh

. ./build.sh $@

DEST_LIB_PATH="/usr/local/lib/"
DEST_INCLUDE_PATH="/usr/local/include/"

if [ ! -w $DEST_INCLUDE_PATH ] || [ ! -w $DEST_LIB_PATH ]; then
	echo "No write permissions. Maybe try sudo ?"
	exit
fi

cp -r $INCLUDE_DIR/* $DEST_INCLUDE_PATH/$LIB_NAME/
cp $BUILD_DIR/$LIB_FILE_NAME $DEST_LIB_PATH
