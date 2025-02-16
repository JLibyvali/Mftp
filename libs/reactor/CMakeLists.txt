set ( all_srcs
    constant.cpp
    resource_init.cpp
    sigact.cpp
    CACHE INTERNAL
    "Reactor library sources" )

add_library ( reactor ${all_srcs} )

target_include_directories ( reactor
    PUBLIC # Why set as PUBLIC? May reactor.hpp contains another header files definition
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
