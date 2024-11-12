file(GLOB basic_srcs "./*.cpp")
file(GLOB basic_header_impl "include/*.cpp")

file(GLOB reactor_srcs "./Reactor/*.cpp")

set(SRCS_FILES_KERNEL 
    ${basic_srcs}
    ${basic_header_impl}
    ${reactor_srcs}
    
    PARENT_SCOPE
)