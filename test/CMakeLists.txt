cmake_minimum_required(VERSION 3.28)
project(Test)

macro(compile _name)
    add_executable(${_name} ${src} ${header})
endmacro(compile _name)

# Build given name test target
function(build_test _what)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY test)

    # build test _what
    file(GLOB_RECURSE src "test/${_what}/*.cpp")
    file(GLOB_RECURSE header "test/${_what}/*.hpp")
    info("Test files: ${src}\n${header}")
    compile("${_what}")
endfunction()