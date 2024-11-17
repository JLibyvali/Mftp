cmake_minimum_required ( VERSION 3.28 )
project ( Mftp )

# config
include ( cmake/toolchain.cmake )
include ( cmake/package.cmake )
add_debug_flag(check_build template_error)


# add_CLI11()

# include_directories(include)
# include_directories(src/kernel/include)
# add_subdirectory(src)
# add_executable(${PROJECT_NAME} ${SRCS_FILES})

# add test 
add_CLI11()
add_Libuv()
add_Reactor()
add_test(test_Libuv test_Reactor)