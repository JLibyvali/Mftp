#!/bin/bash
cur=$(pwd)

cmake_files=$(find $cur  -type f \( -name "*.cmake" -o -name "CMakeLists.txt" \))

# check if clang-format installed
if ! command -v cmake-format &> /dev/null; then
    echo "Cannot find clang-foramt"
    exit 1;
fi  

# Format
for file in $cmake_files; do
    echo "Formattign $file"
    cmake-format $file  --config-file $cur/.cmake-format.json -i 
done

echo "Formated all files"