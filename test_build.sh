#!/bin/sh
cur=$(pwd)
cmake_file=$cur/test/CMakeLists.txt

if [ -d test-build ]; then
    rm -r test-build
fi

mkdir test-build
cd test-build

cmake $cmake_file
