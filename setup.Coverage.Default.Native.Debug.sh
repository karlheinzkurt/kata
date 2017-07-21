#!/bin/bash
DIR="$( cd "$(dirname "$0")" ; pwd -P )"
BUILD_DIR=$DIR/build/Coverage
BIN_DIR=$DIR/bin/Coverage
SOURCE_DIR=$DIR/Source

if [ ! -d "$BUILD_DIR" ]; then
   mkdir -p $BUILD_DIR
   pushd $BUILD_DIR
      cmake \
		-DBIN_PATH_POSTFIX=Coverage\
		-DCMAKE_BUILD_TYPE=Coverage\
		$SOURCE_DIR 
		cmake --build $BUILD_DIR --config Debug
   popd
fi

find $BIN_DIR -maxdepth 1 -name "*.Test" -exec {} \;
gcovr \
   -e ".+Test\.cpp"\
   -e ".+main.cpp"\
   -e ".+gmock/.+"\
   -r $DIR/../\
   --object-directory=$BUILD_DIR\
   > $BUILD_DIR/coverage.txt
cat $BUILD_DIR/coverage.txt
