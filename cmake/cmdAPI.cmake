# Warp infomation output
function(info type arg)
    message(${type} "@@@@@@@@@{ ${arg} }@@@@@@@")
endfunction()

# function to build a series of executables
function(build_executables _name_list _src_list)
    list(LENGTH _name_list len)

    foreach(i RANGE ${${len}-1})
        list(GET _name_list ${i} _name)
        list(GET _src_list ${i} _srcs)
        add_executable(${_name} ${_srcs})
    endforeach()
endfunction(build_executables)
