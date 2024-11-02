include(${CMAKE_SOURCE_DIR}/cmake/cmdAPI.cmake)
# ######################################################################################################################################################################################################
# Language
# ######################################################################################################################################################################################################
enable_language ( C CXX )
set ( CMAKE_C_STANDARD 99 )
set ( CMAKE_C_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

# ######################################################################################################################################################################################################
# Compiler and  linker                                                  
# ######################################################################################################################################################################################################
# ######################################################################################################################################################################################################
# architecure related flags
# ######################################################################################################################################################################################################
# -m64 "The -m64 option sets int to 32 bits and long and pointer types to 64 bits, and generates code for the x86-64 architecture. For Darwin only the -m64 option also turns off the -fno-pic and
# -mdynamic-no-pic options." -march=x86       "-march=cpu-type allows GCC to generate code that may not run at all on processors other than the one indicated. " -fcf-protection  "nable code
# instrumentation of control-flow transfers to increase program security by checking that target addresses of control-flow transfer instructions (such as indirect function call, function return,
# indirect jump) are valid"
set ( FLAG_X86_64 "-m64 -march=x86-64 -fcf-protection=full" CACHE STRING "Add compiler flags of X86_64 arch" )
set ( _FALG_RK3566 CACHE STRING "Add compiler flags of RK3566 soc" )

# ######################################################################################################################################################################################################
# debug related  flags
# ######################################################################################################################################################################################################
# -g/ggdb <level>   "Level 3 includes extra information, such as all the macro definitions present in the program. Some debuggers support macro expansion when you use -g3." -O0   "No optmization,
# faster compilation time, better for debugging builds." -Wall "Turns on lots of compiler warning flags," FOR ASLR -fpic "Generate position-independent code (PIC) suitable for use in a shared library,
# if supported for the target machine" FOR ASLR -fpie "These options are similar to -fpic and -fPIC, but the generated position-independent code can be only linked into executables" -fexceptions
# "Enable exception handling. Generates extra code needed to propagate exceptions. Recommed for multithreads" -fstack-protector-strong "Like -fstack-protector but includes additional functions to be
# protected — those that have local array definitions, or have references to local frame addresses. " -fstack-check  "Generate code to verify that you do not go beyond the boundary of the stack. You
# should specify this flag if you are running in an environment with multiple threads," -fstack-clash-protection "Generate code to prevent stack clash style attacks. When this option is enabled, the
# compiler will only allocate one page of stack space at a time and each page is accessed immediately after allocation. " -funroll-all-loops "Unroll all loops, even if their number of iterations is
# uncertain when the loop is entered. This usually makes programs run more slowly. -funroll-all-loops implies the same options as -funroll-loops,"
set ( FLAG_DEBUG "-O0 -g3 -ggdb3 -Wall -fpic -fpie -fexceptions -fstack-protector-strong -fstack-check -fstack-clash-protection -funroll-all-loops" CACHE STRING
    "Add Compiler flag When cmake debug variant" )

# ######################################################################################################################################################################################################
# Production flags
# ######################################################################################################################################################################################################
# -ffunction-sections   "Place each function or data item into its own section in the output file if the target supports arbitrary sections. The name of the function or the name of the data item
# determines the section’s name in the output file." -fdata-section’s  "small size output file" -fno-delete-null-pointer-checks ""
set ( FLAG_PRODUCTION "-O3 -fpic -fpie -ffunction-sections -fdata-sections" CACHE STRING "Add compiler flags when cmake release variant" )

# ######################################################################################################################################################################################################
# Perfomance tools related
# ######################################################################################################################################################################################################
# -fasynchronous-unwind-tables " is required for many debugging and performance tools to work on most architectures" -pg "For gprof" -fsanitize=address "Enable AddressSanitizer, a fast memory error
# detector. Memory access instructions are instrumented to detect out-of-bounds and use-after-free bugs." -fsanitize=thread "" -fsanitize=leak "" -fsanitize=undefined
set ( FLAG_PERFTOOLS "-fasynchronous-unwind-tables -pg" CACHE STRING "Add compiler flags of Performance tools need" )
set ( FLAG_SANITIZER "-fsanitize=address -fsanitize=leak -fsanitize=thread -fsanitize=undefined" CACHE STRING "Add compiler flags for google-sanitier" )

# ######################################################################################################################################################################################################
# Check gcc switches
# ######################################################################################################################################################################################################
# -grecord-gcc-switches "captures compiler flags, which can be useful to determine whether the intended compiler flags are used throughout the build."
set ( FLAG_CHECK_BUILD "-grecord-gcc-switches" CACHE STRING "Add falg for  checking gcc switches" )

# ######################################################################################################################################################################################################
# linker flag
# ######################################################################################################################################################################################################
# -pie "Produce a dynamically linked position independent executable on targets that support it." -sahred "Produce a shared object which can then be linked with other objects to form an executable."
# -Map "Create a map file for debug" -fuse-ld "Use the gold linker instead of the default linker." -flto " hen the object files are linked together, all the function bodies are read from these ELF
# sections and instantiated as if they had been part of the same translation unit." -fuse-linker-plugin "This option enables the extraction of object files with GIMPLE bytecode out of library
# archives. This improves the quality of optimization by exposing more code to the link-time optimizer."
set ( FLAG_LINKER_SMALL "-fuse-linker-plugin --gc-sections -flto" CACHE STRING "Add linker flag for small output file" )
set ( FLAG_LINKER "-pie -shared -Map=symbols.map -fues-ld=gold" CACHE STRING "Add some basic liner flag" )

# ######################################################################################################################################################################################################
# Macro sets
# ######################################################################################################################################################################################################
# _FORTIFY_SOURCE "Check some Glibc function buffer safe" _GLIBCXX_ASSERTIONS "When defined, enables extra error checking in the form of precondition assertions, such as bounds checking in strings and
# null pointer checks when dereferencing smart pointers."
set ( MACRO_DEBUG "_FORTIFY_SOURCE=2 _GLIBCXX_ASSERTIONS" CACHE STRING "Add cmake macro" )

# Init basic compier flag
set ( CMAKE_C_FLAGS_DEBUG ${FLAG_DEBUG} )
set ( CMAKE_C_FLAGS_RELEASE ${FLAG_PRODUCTION} )
set ( CMAKE_EXE_LINKER_FLAGS ${FLAG_LINKER} )
set ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} )
set ( CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} )


# function to add another compiler flag
function ( add_debug_flag )
    set ( options _arch_flag _small_link _perf_tools _sanitizer _debug_macro _check_build )
    set ( multivalue _custom )
    cmake_parse_arguments ( PARSE_ARGV 0 _arg "${options}" "" "${multivalue}" )

    # add some defined flags
    if ( _arg_arch_falg )
        list ( APPEND CMAKE_C_FLAGS_DEBUG ${FLAG_X86_64} )
    elseif ( _arg_small_link )
        list ( APPEND CMAKE_C_FLAGS_DEBUG ${FLAG_LINKER_SMALL} )
    elseif ( _arg_perf_tools )
        list ( APPEND CMAKE_C_FLAGS_DEBUG ${FLAG_PERFTOOLS} )
    elseif ( _arg_sanitizer )
        list ( APPEND CMAKE_C_FLAGS_DEBUG ${FLAG_SANITIZER} )
    elseif ( _arg_check_build )
        list ( APPEND CMAKE_C_FLAGS_DEBUG ${FLAG_CHECK_BUILD} )
    elseif ( _arg_debug_macro )
        foreach ( macro ${MACRO_DEBUG} )
            info ( STATUS "Set macro: ${macro}" )
            set ( ${macro} PARENT_SCOPE )
        endforeach ()
    endif ()

    set ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} )

    # Add other cust flags
    if ( _arg_custom )
        foreach ( _flag ${_arg_custom} )
            info ( STATUS "Add Custom flag: ${_flag}" )
            list ( APPEND CMAKE_C_FLAGS_DEBUG ${_flag} )
        endforeach ( _flag ${_arg_custom} )

        set ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} )
    endif ()
endfunction ()
