cmake_minimum_required ( VERSION 3.28 )
project ( Mftp )

# config
include ( cmake/toolchain.cmake )
include ( cmake/package.cmake )
add_debug_flag ( _custom "-fno-elide-type" )
include_directories(include)
include_directories(src/kernel/include)

add_CLI11()

add_subdirectory(src)
add_executable(${PROJECT_NAME} ${SRCS_FILES})

# add test 