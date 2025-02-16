cmake_minimum_required ( VERSION 3.28 )
project ( Mftp VERSION 0.1.0 )

# ----------------------------------------------------------
# Include cmake modules and Headers
# ----------------------------------------------------------
list ( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
include ( Api )
include ( ToolChain )
include ( Package )

include_directories ( include include/kernel include/gui )

# ----------------------------------------------------------
# Add libraries target
# ----------------------------------------------------------
add_Boost ()
add_CLI11 ()
add_Asio ()
add_Tinyprocess ()
add_Benchmark ()
add_CustomLib()


# ----------------------------------------------------------
# Project Building
# ----------------------------------------------------------
# add_subdirectory ( src )

# ----------------------------------------------------------
# Build Test Objectsc
# ----------------------------------------------------------
add_subdirectory ( test )