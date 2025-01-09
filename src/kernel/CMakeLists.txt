set(basic_srcs
        main.cpp)
set(basic_header_impl
        include/Arg_parser.cpp
        include/Config.cpp
        include/Event.cpp
        include/User.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${basic_srcs} ${basic_header_impl})