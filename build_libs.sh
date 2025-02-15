#!/bin/bash

set -e


cur=$(pwd)
SYSTEM="$cur/System"
INSTALL="$SYSTEM/install"
BENCHMARK="$SYSTEM/3rdpart/benchmark"
CPPZMQ="$SYSTEM/3rdpart/cppzmq"
IPERF="$SYSTEM/3rdpart/iperf"
JSON="$SYSTEM/3rdpart/json"
LIBUV="$SYSTEM/3rdpart/libuv"
TINY="$SYSTEM/3rdpart/tiny-process-library"


#--------------------------------------------------------------------------------------------------------------------------
# Build benchmark library both static and dynamic
#--------------------------------------------------------------------------------------------------------------------------

BENCHMARK_OPTS="-DCMAKE_BUILD_TYPE=Release -DBENCHMARK_DOWNLOAD_DEPENDENCIES=OFF -DBENCHMARK_ENABLE_TESTING=OFF -DBENCHMARK_USE_BUNDLED_GTEST=OFF"
echo "-------------------------- Build Benchmark Library -------------------------------------"
cd $BENCHMARK
cmake -E make_directory "BUILD"
cmake -E chdir "BUILD" cmake -GNinja -DCMAKE_INSTALL_PREFIX=$INSTALL $BENCHMARK_OPTS  ..
cmake --build "BUILD" --config Release  --parallel 8 

cd $BENCHMARK/BUILD
cmake --install . 


echo "-------------------------- Build CPP ZMQ -------------------------------------"
cd $CPPZMQ
cmake -E make_directory "BUILD"
cmake -E chdir "BUILD" cmake -GNinja -DCMAKE_INSTALL_PREFIX=$INSTALL -DCPPZMQ_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ..
cmake --build "BUILD" --config Release  --parallel 8

cd $CPPZMQ/BUILD
cmake --install .


echo "-------------------------- Build JSON library ----------------------------------------"
cd $JSON
cmake -E make_directory "BUILD"
cmake -E chdir "BUILD" cmake -GNinja -DCMAKE_INSTALL_PREFIX=$INSTALL -DCMAKE_BUILD_TYPE=Release -DJSON_BuildTests=OFF ..
cmake --build "BUILD" --config Release  --parallel 8

cd $JSON/BUILD
cmake --install .


echo "-------------------------- Build Libuv ------------------------------------------------------------"
cd $LIBUV
cmake -E make_directory "BUILD"
cmake -E chdir "BUILD" cmake -GNinja -DCMAKE_INSTALL_PREFIX=$INSTALL -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF  ..
cmake --build "BUILD" --config Release  --parallel 8

cd $LIBUV/BUILD
cmake --install .


echo "-------------------------- Build tiny process library ------------------------------------------------"
cd $TINY
cmake -E make_directory "BUILD"
cmake -E chdir "BUILD" cmake -GNinja -DCMAKE_INSTALL_PREFIX=$INSTALL -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON  .. 
cmake --build "BUILD" --config Release  --parallel 8

cd $TINY/BUILD
cmake --install .


echo "-------------------------- Build Iperf library ----------------------------------------------------------"
cd $IPERF

./configure --prefix=$INSTALL
make -j 8
make install
