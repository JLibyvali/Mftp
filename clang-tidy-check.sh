#!/bin/bash

# set -e, -u, -o pipefail for script error handling
set -e
cur="$(pwd)"

BUILD_DIR="./build"
SOURCE_DIR="./src/kernel"
CLANG_TIDY_CFG="./.clang-tidy"
RUN_CLANG_TIDY="./clang-tools/run-clang-tidy.py"

function info(){
    echo ">> $(date '+%Y-%m-%d %H:%M:%S') $*"
}

function cmd(){
    info "@$*"
    $@ 2>&1
}

function join_list(){
    local IFS="$1"
    shift
    echo "$@"
}

function fix_all(){
    
    # Some stable fix option
    AUTO_FIX_CHECKS_CFG=(
    "-*"
    "modernize-use-nullptr"
    "modernize-use-override"
    "modernize-use-using"
    "modernize-make-shared"
    "boost-use-to-string"
    "readability-container-size-empty"
    "readability-redundant-access-specifiers"
    "readability-redundant-string-cstr"
    "readability-redundant-string-init"
    "readability-redundant-smartptr-get"
    "readability-redundant-control-flow"
    "google-readability-namespace-comments"
    "performance-unnecessary-copy-initialization"
    "performance-for-range-copy"
    "performance-noexcept-move-constructor"
    "clang-analyzer-deadcode.DeadStores"
  )
  AUTO_FIX_CHECKS=$(join_list "," "${AUTO_FIX_CHECKS_CFG[@]}")

  info "$RUN_CLANG_TIDY" -use-color '1' -p "$BUILD_DIR" -checks="$AUTO_FIX_CHECKS" -j "$(nproc)" -fix "$SOURCE_DIR"
  
  "$RUN_CLANG_TIDY" -use-color '1' -p "$BUILD_DIR" -checks="$AUTO_FIX_CHECKS" -j "$(nproc)" -fix "$SOURCE_DIR"
  echo "Fix done"
}

function check_all(){
    info "$RUN_CLANG_TIDY" -use-color '1' -p "$BUILD_DIR" -config-file "$CLANG_TIDY_CFG"  -j "$(nproc)" "$SOURCE_DIR" 

    "$RUN_CLANG_TIDY" -use-color '1' -p "$BUILD_DIR" -config-file "$CLANG_TIDY_CFG" -j "$(nproc)"  "$SOURCE_DIR" > /tmp/clang-tidy.log  2>&1  # generate log file
    
    {
        echo "Clang-tidy check result: "
        echo '```'
        echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Error checked "
        grep --color=always -s -A 2 -E "error:.*\[.*\]" /tmp/clang-tidy.log || :;
        echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Warning checked "
        grep --color=always -s -A 2 -E "warning:.*\[.*\]" /tmp/clang-tidy.log || :;
        echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@REPORT@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
        grep --color=always -s -A 2 -E "error:.*\[.*\]|warning:.*\[.*\]" /tmp/clang-tidy.log | grep --color=always -Eo "\[.*\]" | sort | uniq -c | sort -n  
        echo '```'
        echo "Clang-tidy check done"
    } > /tmp/clang-tidy-summary.log
        
    cat /tmp/clang-tidy-summary.log

}


function func_diff(){
    case $1 in 
    check)

        ;;
    fix)
        ;;
    *)
        echo "Usage $0 [fix] [check]"
        ;;
    esac

}

 
case $1 in 
check)
    check_all
    ;;
fix)
    fix_all
    ;;
diff_check)
    echo "DIFF"
    ;;
diff_fix)
    echo "DIFF fix"
    ;;
*)
    echo "Invalid args: $*"
    ;;
esac