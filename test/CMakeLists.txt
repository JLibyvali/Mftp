cmake_minimum_required ( VERSION 3.28 )
project ( Test )

include ( ../cmake/cmdAPI.cmake)

# add all subdirectory
file ( GLOB test_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "test_*" )
foreach ( _dir IN ${test_dirs} )
    if (IS_DIRECTORY ${_dir})
        add_subdirectory ( ${_dir} )
    endif ()
endforeach (_dir IN ${test_dirs})

# Extract name_list and name_srcs_list
cmake_language(CALL extract_vars "$_TEST_srcs" test_src_vars)

if(test_src_vars)
    set(name_list "")
    set(name_src_list "")
    
    # extract names and name_srcs
    foreach(test_var IN ${test_src_vars})
        string(REGEX MATCH "^[^_]+" test_target_name ${test_var})
        list(APPEND name_list ${test_target_name})

        # append srcs
        list(APPEND name_src_list "${${test_var}}") 
    endforeach()

    # Generate executables
    cmake_language(CALL build_executables ${name_list} ${name_src_list})
else()
    info(FATAL_ERROR "Can't find test target source files, no \{test_src_vars\}")
endif()