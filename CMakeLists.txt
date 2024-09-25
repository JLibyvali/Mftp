cmake_minimum_required(VERSION 3.20)

project(M-Webserver)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


####### Debug and Release Compiler Flags

##### Set Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Sql)

set(SOURCES
FileSystem/FileOptons.cpp
FileSystem/FileSystem.cpp
FileSystem/IODevice.cpp
Person/person.cpp 
UI/UI_MWidgets.cpp
UI/UI_Menus.cpp
UI/MainWindow.cpp
Action/TreeViewAction.cpp

main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
.
Action
Exception 
FileSystem 
Person 
UI 
)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets 
Qt6::Core 
Qt6::Gui)
