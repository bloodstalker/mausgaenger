#!/usr/bin/bash

"clang" --version > /dev/null 2>&1
if [[ $? != 0 ]];then echo couldnt find clang;fi
"llc" --version > /dev/null 2>&1
if [[ $? != 0 ]];then echo couldnt find llc;fi
"s2wasm" -h > /dev/null 2>&1
if [[ $? != 0 ]];then echo couldnt find s2wasm;fi
"wast2wasm" -h > /dev/null 2>&1
if [[ $? != 0 ]];then echo couldnt find wast2wasm;fi

fullname=$1
namelength=${#fullname}
offset=$((${#fullname} - 2))
filename=${fullname:0:$offset}

"clang" -emit-llvm --target=wasm32 -Oz "$1" -c
"llc" -asm-verbose=false -o $filename.s $filename.bc
"s2wasm" $filename.s > $filename.wast
"wast2wasm" $filename.wast -o $filename.wasm
