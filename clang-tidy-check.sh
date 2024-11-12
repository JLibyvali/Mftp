#!/bin/bash

set -euo pipefail

function info(){
    echo ">> $(date '+%Y-%m-%d %H:%M:%S') $*"
}

function join_list(){
    local IFS="$1"
    shift
    echo "$@"
}

BUILD_DIR="./build"
# SOURCE_DIR=${CI_PROJECT_DIR:-${$pwd}}
info "build project in: $BUILD_DIR"
# info "source dir: $SOURCE_DIR"


case $1 in 
check)
    echo "Input check"
    ;;
fix)
    echo "Using clang-tidy fix code"
    ;;
*)
    echo "Invalid args: $*"
    ;;
esac