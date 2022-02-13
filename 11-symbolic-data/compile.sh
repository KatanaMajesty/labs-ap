#!/bin/bash
echo off
cmake -G "Unix Makefiles" -B ./build -S .

cd ./build
make

./laboratory-11