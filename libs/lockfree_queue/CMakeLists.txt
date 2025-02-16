set ( LFQ_srcs
    lf_queue.cpp
    lf_queue.hpp
    lf_queue.tpp

    wrap_boost.hpp
    wrap_boost.tpp
    CACHE INTERNAL
    "Lock Free Library sources." )

add_library ( lockfree_queue STATIC ${LFQ_srcs} )
target_link_libraries ( lockfree_queue PRIVATE Boost::headers )
target_include_directories ( lockfree_queue
    PUBLIC ${CMAKE_SOURCE_DIR}/libs/lockfree_queue )