file(GLOB all_srcs "./*.cpp")
file(GLOB all_header_impl "include/*.cpp")

set(SRCS_FILES_KERNEL 
    ${all_srcs}
    ${all_header_impl}
    
    PARENT_SCOPE
)