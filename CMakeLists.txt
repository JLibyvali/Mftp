cmake_minimum_required ( VERSION 3.28 )
project ( Mftp VERSION 0.1.0 )

# ----------------------------------------------------------
# Include cmake modules and Headers
# ----------------------------------------------------------
include ( cmake/api.cmake )
include ( cmake/toolchain.cmake )
include ( cmake/package.cmake )
include_directories ( include include/kernel include/gui )

# ----------------------------------------------------------
# Add libraries configurations
# ----------------------------------------------------------
add_CLI11 ()

# ----------------------------------------------------------
# Project Building
# ----------------------------------------------------------
add_subdirectory ( src )

# ----------------------------------------------------------
# Build Test Objectsc
# ----------------------------------------------------------