#!/bin/bash
DIR="$( cd "$(dirname "$0")" ; pwd -P )"
BUILD_DIR=$DIR/build/Coverage
BIN_DIR=$DIR/bin
SOURCE_DIR=$DIR/Source

if [ ! -d "$BUILD_DIR" ]; then
   mkdir -p $BUILD_DIR
   pushd $BUILD_DIR
      cmake -DCMAKE_BUILD_TYPE=Coverage $SOURCE_DIR
   popd
fi

pushd $BUILD_DIR
   make -B
popd

find $BIN_DIR -maxdepth 1 -name "*.Test" -exec {} \;
gcovr \
   -e ".+Test\.cpp"\
   -e ".+main.cpp"\
   -e ".+gmock/.+"\
   -r $DIR/../\
   --object-directory=$BUILD_DIR\
   > $BUILD_DIR/coverage.txt
cat $BUILD_DIR/coverage.txt
