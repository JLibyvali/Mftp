cmake_minimum_required(VERSION 3.20)

project(server)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
enable_language(C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "-g -O0 -ggdb3 -Wall")

set(SRC_LIST  
socket.cpp)


add_executable(${PROJECT_NAME} ${SRC_LIST})