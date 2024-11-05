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

function ( add_reproc )
    set ( REPROC++ ON )
    set ( BUILD_SHARED_LIBS ON )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/3rdpart/reproc )
    link_libraries ( reproc++ )
endfunction ()

# Add build test target name
function ( add_test )
    set ( prefix arg )
    set ( options test_CLI11 test_Reproc test_Libuv )
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
