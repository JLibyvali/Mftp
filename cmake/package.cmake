# Set for qt
function ( add_qt )
    set ( CMAKE_AUTOMOC ON )
    set ( CMAKE_AUTOUIC ON )
    set ( CMAKE_AUTORCC ON )

    find_package ( Qt6 REQUIRED COMPONENTS Widgets Core Gui )
    link_libraries ( Qt6::Core Qt6::Gui Qt6::Widgets )
endfunction ()

# CLI11
function ( add_CLI11 )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/3rdpart/CLI11 )
    link_libraries ( CLI11::CLI11 )
endfunction ()

function ( add_Tinyprocess )
    set ( BUILD_SHARED_LIBS ON )

    # find interface header
    find_path ( tinyProcess_Head
        NAMES "process.hpp"
        HINTS "${CMAKE_SOURCE_DIR}/libs/3rdpart/tiny-process-library"
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH )

    if ( NOT tinyProcess_Head )
        info ( FATAL_ERROR "Can not find tiny_Process library" )
    endif ()

    add_subdirectory ( "${CMAKE_SOURCE_DIR}/libs/3rdpart/tiny-process-library" )

    if ( NOT TARGET tiny-process-library )
        info ( FATAL_ERROR "tiny-process-library compiled failed" )
    endif ()

    link_libraries ( tiny-process-library )
endfunction ()

function ( add_Asio )
    find_path ( asio_Head
        NAMES asio.hpp
        HINTS "${CMAKE_SOURCE_DIR}/libs/3rdpart/asio/asio/include"
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH
    )

    # Try find asio.hpp the interface
    if ( NOT asio_Head )
        info ( FATAL_ERROR "Can not find ASIO library" )
    endif ()

    # Compile the asio  library
    set ( asio_INCLUDE_DIR ${asio_Head} )

    # Add asio::asio manually
    if ( NOT TARGET asio::asio )
        add_library ( asio::asio INTERFACE IMPORTED )
        set_target_properties ( asio::asio PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${asio_INCLUDE_DIR}
                INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE ) # Without boost dependency
    endif ()

    link_libraries ( asio::asio )
endfunction ()

# Add build test target name
function ( add_test )
    set ( prefix arg )
    set ( options test_CLI11 test_Tinyprocess test_Libuv test_ASIO )
    cmake_parse_arguments ( PARSE_ARGV 0 ${prefix} "${options}" "" "" )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/test )

    foreach ( opt ${options} )
        set ( var "${prefix}_${opt}" )

        if ( ${var} )
            build_test ( ${opt} )
        endif ()
    endforeach ()

    # IF any unparsed
    if ( arg_UNPARSED_ARGUMENTS )
        info ( STATUS "Unparsed input arguments: ${arg_UNPARSED_ARGUMENTS}" )
    endif ()
endfunction ()
