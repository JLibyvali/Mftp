add_library ( memorypool STATIC memorypool.cpp )
target_include_directories ( memorypool PUBLIC ${CMAKE_SOURCE_DIR}/libs/memorypool )