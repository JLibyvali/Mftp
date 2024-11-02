include(${CMAKE_SOURCE_DIR}/cmake/cmdAPI.cmake)

# Set for qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
