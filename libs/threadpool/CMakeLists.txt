add_library ( threadpool STATIC
    threadpool.cpp
    threadpool.hpp
    threadpool.tpp
)

target_link_libraries ( threadpool PRIVATE Boost::headers )
target_include_directories ( threadpool PUBLIC ${CMAKE_SOURCE_DIR}/libs/threadpool )