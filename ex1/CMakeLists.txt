project(ex1)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/Action
    ${CMAKE_CURRENT_LIST_DIR}/Exception
    ${CMAKE_CURRENT_LIST_DIR}/Connect
)

add_executable(
    ${PROJECT_NAME}  ${SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)