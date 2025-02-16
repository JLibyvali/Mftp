# ####################################################################################################
# Add Some Depends Initialize Functions
# ####################################################################################################
list ( APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/System/install" )
include_directories ( BEFORE ${CMAKE_SOURCE_DIR}/System/install/include )
set ( SELF_LIBS )

macro ( add_qt )
    set ( CMAKE_AUTOMOC ON )
    set ( CMAKE_AUTOUIC ON )
    set ( AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/gui )
    set ( CMAKE_AUTORCC ON )

    find_package ( Qt6 REQUIRED COMPONENTS Widgets Core Gui )
    link_libraries ( Qt6::Core Qt6::Gui Qt6::Widgets )
endmacro ()

macro ( add_CLI11 )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/3rdpart/CLI11 )
endmacro ( add_CLI11 )

macro ( add_Tinyprocess )
    find_package ( Threads REQUIRED )
    find_package ( tiny-process-library REQUIRED COMPONENTS tiny-process-library )
endmacro ( add_Tinyprocess )

macro ( add_Boost )
    set ( Boost_USE_RELEASE_LIBS ON )
    set ( Boost_USE_STATIC_LIBS ON )
    find_package ( Boost 1.83.0 REQUIRED COMPONENTS filesystem system )
endmacro ()

macro ( add_Benchmark )
    find_package ( benchmark REQUIRED )
endmacro ()

function ( add_Asio )
    find_path ( asio_Head
        NAMES asio.hpp
        HINTS "${CMAKE_SOURCE_DIR}/libs/3rdpart/asio/asio/include"
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH
    )

    # Try find asio.hpp the interface
    if ( NOT asio_Head )
        message ( FATAL_ERROR "Can not find ASIO library" )
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
endfunction ()

# ####################################################################################################
# Add Custom Libraries
# ####################################################################################################
function ( add_CustomLib )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/reactor )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/lockfree_queue )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/threadpool )
    add_subdirectory ( ${CMAKE_SOURCE_DIR}/libs/memorypool )
    list ( APPEND SELF_LIBS reactor lockfree_queue threadpool memorypool )

    info ( "Current Libs: ${SELF_LIBS} " )
endfunction ()