# Warp infomation output
function ( info type arg )
    message ( ${type} "@@@@@@@@@{ ${arg} }@@@@@@@" )
endfunction ()

# function to build a series of executables
function ( build_executables _name_list _src_list )
    if ( _name_list AND _src_list )
        info ( STATUS "Build executable: ${_name_list}" )

        foreach ( i RANGE 0 $<STREQUAL:${name_list}> )
            list(GET _name_list ${i} _name)
            list(GET _src_list ${i} _srcs)

            add_executable(${_name} ${_srcs})
        endforeach ()

    elseif ()
        info ( FATAL_ERROR "None \{_name\} or \{_src\}" )
    endif ()
endfunction ( build_executables _name_list _src_list )

# function to extract cmake variables
function ( extract_vars _input_var vars_list )
    set ( vars_list "" )

    if ( NOT _input_var )
        return ( PROPAGATE ${_input_var} )
    endif ()

    # traverse all variables to extract
    get_cmake_property ( all_vars VARIABLES )

    foreach ( var IN ${all_vars} )
        if ( ${var} MATCHES ${_input_var} )
            list ( APPEND vars_list ${var} )
        endif ()
    endforeach ()

    info ( STATUS "Extract variables res: ${vars_list}" )
    return ( PROPAGATE ${vars_list} )
endfunction ( extract_vars _input_var )
