#!/bin/bash

echo Determining C-compiler
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo Detected ${machine} compiler
if [[ ${machine} == MinGW ]]; then
    echo This is not meant for MinGW lmao
fi

echo on
cmake -G "Unix Makefiles" -B ./build -S .

cd ./build
make

./$1/$1 # will execute executable from CLI argument list