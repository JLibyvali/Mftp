# ----------------------------------------------------------
# Project Building
# ----------------------------------------------------------
include ( ${CMAKE_SOURCE_DIR}/cmake/package.cmake )
add_lockfree_queue()

add_executable ( ${PROJECT_NAME} )
target_link_libraries ( ${PROJECT_NAME} PRIVATE ${SELF_LIBS} )
add_subdirectory ( kernel )
