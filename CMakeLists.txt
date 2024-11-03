cmake_minimum_required(VERSION 3.28)
project(Mftp)

include(cmake/package.cmake)
include(cmake/toolchain.cmake)

# # Control target linked add_executable(${PROJECT_NAME} ${SRCS_FILES})

# # linked Qt target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

# test
add_subdirectory(test)
build_test()
