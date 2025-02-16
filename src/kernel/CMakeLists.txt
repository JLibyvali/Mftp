set ( basic_srcs
        init.cpp
)
set ( basic_header_impl
        include/Arg_parser.cpp
        include/Config.cpp
        include/User.cpp )

target_sources ( ${PROJECT_NAME} PRIVATE ${basic_srcs} ${basic_header_impl} )