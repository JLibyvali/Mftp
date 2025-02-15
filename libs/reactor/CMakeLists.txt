cmake_minimum_required ( VERSION 3.28 )
project ( reactor )

# Compile as a library
set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )
set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set ( all_srcs
    ./constant.cpp
    ./resource_init.cpp
    ./sigact.cpp
    CACHE INTERNAL
    "Reactor's library sources" )

add_library ( ${PROJECT_NAME} ${all_srcs} )

target_include_directories ( ${PROJECT_NAME}
    PUBLIC # Why set as PUBLIC? May reactor.hpp contains another header files definition
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
