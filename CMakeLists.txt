cmake_minimum_required(VERSION 3.20)

project(qtexamples)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


####### Debug and Release Compiler Flags

##### Set Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Sql)

####### Sub directory
add_subdirectory(ex1)



