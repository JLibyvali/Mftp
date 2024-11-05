cmake_minimum_required(VERSION 3.28)
project(Mftp)

# comfig
include(cmake/toolchain.cmake)
include(cmake/package.cmake)
add_debug_flag(_custom "-fno-elide-type")


# test
add_reproc()
add_test(test_Reproc)