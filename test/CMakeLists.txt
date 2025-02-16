include ( CTest )

add_executable ( test_cli11 test_CLI11/cli.cpp test_CLI11/cli.hpp )
target_link_libraries ( test_cli11 PRIVATE CLI11::CLI11 )

add_executable ( test_reactor treactor.cpp )
target_link_libraries ( test_reactor PRIVATE reactor )

add_executable ( test_tinyp tp.cpp )
target_link_libraries ( test_tinyp PRIVATE tiny-process-library::tiny-process-library )

add_executable ( test_lfqueue test_lfqueue.cpp )
target_link_libraries ( test_lfqueue PRIVATE benchmark::benchmark PRIVATE lockfree_queue )

add_executable ( test_threadpool test_threads.cpp )
target_link_libraries ( test_threadpool PRIVATE threadpool)
