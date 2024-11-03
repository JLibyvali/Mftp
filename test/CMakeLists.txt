cmake_minimum_required(VERSION 3.28)
project(Test)

set(src "")
set(header "")

function(compile _name)
    add_executable(${_name} ${src} ${header})
endfunction(compile _name)

# test
function(build_test)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "/home/jlibyvali/Developer/projetcs/Mftp/test-build")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "/home/jlibyvali/Developer/projetcs/Mftp/test-build")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/jlibyvali/Developer/projetcs/Mftp/test-build/bin")

    # test_CLI
    file(GLOB_RECURSE src "test_CLI/*.cpp")
    file(GLOB_RECURSE header "test_CLI/*.h")
    compile("test_CLI")

    # test_libuv
    file(GLOB_RECURSE src "test_libuv/*.cpp")
    file(GLOB_RECURSE header "test_libuv/*.h")
    compile("test_libuv")
endfunction()
