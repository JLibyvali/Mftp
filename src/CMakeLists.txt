# ----------------------------------------------------------
# Project Building
# ----------------------------------------------------------
add_executable ( ${PROJECT_NAME} main.cpp)

target_link_libraries ( ${PROJECT_NAME} PRIVATE ${SELF_LIBS} CLI11::CLI11 )
add_subdirectory ( kernel )
