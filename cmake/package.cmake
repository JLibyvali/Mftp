# #####################################################
# Add library functions
# #####################################################
function(add_qt)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
    link_libraries(Qt6::Core Qt6::Gui Qt6::Widgets)
endfunction()

function(add_CLI11)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/3rdpart/CLI11)
    link_libraries(CLI11::CLI11)
endfunction()

function(add_Tinyprocess)
    set(BUILD_SHARED_LIBS ON)

    # find interface header
    find_path(tinyProcess_Head
            NAMES "process.hpp"
            HINTS "${CMAKE_SOURCE_DIR}/libs/3rdpart/tiny-process-library"
            NO_DEFAULT_PATH
            NO_CMAKE_FIND_ROOT_PATH)

    if (NOT tinyProcess_Head)
        message(FATAL_ERROR "Can not find tiny_Process library")
    endif ()

    add_subdirectory("${CMAKE_SOURCE_DIR}/libs/3rdpart/tiny-process-library")

    if (NOT TARGET tiny-process-library)
        message(FATAL_ERROR "tiny-process-library compiled failed")
    endif ()

    link_libraries(tiny-process-library)
endfunction()

function(add_Asio)
    find_path(asio_Head
            NAMES asio.hpp
            HINTS "${CMAKE_SOURCE_DIR}/libs/3rdpart/asio/asio/include"
            NO_DEFAULT_PATH
            NO_CMAKE_FIND_ROOT_PATH
    )

    # Try find asio.hpp the interface
    if (NOT asio_Head)
        message(FATAL_ERROR "Can not find ASIO library")
    endif ()

    # Compile the asio  library
    set(asio_INCLUDE_DIR ${asio_Head})

    # Add asio::asio manually
    if (NOT TARGET asio::asio)
        add_library(asio::asio INTERFACE IMPORTED)
        set_target_properties(asio::asio PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${asio_INCLUDE_DIR}
                INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE) # Without boost dependency
    endif ()

    link_libraries(asio::asio)
endfunction()

function(add_Libuv)
    set(BUILD_SHARED_LIBS ON)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/3rdpart/libuv)
    link_libraries(libuv::libuv)
endfunction()

function(add_Reactor)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/reactor)
    link_libraries(reactor)
endfunction()

# -----------------------------------------------------------------------------------#
# Add build test target name
# -----------------------------------------------------------------------------------#
function(add_test)
    set(prefix arg)
    set(options test_CLI11 test_Tinyprocess test_Libuv test_ASIO test_Reactor)
    cmake_parse_arguments(PARSE_ARGV 0 ${prefix} "${options}" "" "")
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)

    foreach (opt ${options})
        set(var "${prefix}_${opt}")

        if (${var})
            build_test(${opt})
        endif ()
    endforeach ()

    # IF any unparsed
    if (arg_UNPARSED_ARGUMENTS)
        info("Unparsed input arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif ()
endfunction()

# -----------------------------------------------------------------------------------#
# Add Self library
# -----------------------------------------------------------------------------------#
set(SELF_LIBS)
function(add_lockfree_queue)
    set(lf_srcs ${CMAKE_SOURCE_DIR}/libs/lockfree_queue/lf_queue.hpp ${CMAKE_SOURCE_DIR}/libs/lockfree_queue/lf_queue.cpp)
    add_library(lockfree_queue ${lf_srcs})

    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    find_package(Boost 1.83.0 REQUIRED COMPONENTS filesystem)
    if (Boost_FOUND)
        target_link_libraries(lockfree_queue PRIVATE Boost::headers)
    elseif ()
        message(FATAL_ERROR "Can't find Boost Library")
    endif ()

    # Add to target list
    list(APPEND SELF_LIBS lockfree_queue)
endfunction()