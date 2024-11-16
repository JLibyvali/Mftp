cmake_minimum_required(VERSION 3.28)
project(reactor)

# Compile as a library
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE all_srcs "*.cpp")

add_library(${PROJECT_NAME} STATIC ${all_srcs})
target_include_directories(${PROJECT_NAME} PRIVATE
.
include
)


