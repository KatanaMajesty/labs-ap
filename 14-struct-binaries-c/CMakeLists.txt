cmake_minimum_required(VERSION 3.2)
project(14-struct-binaries-c C)

include_directories(
    .
)

add_executable(${PROJECT_NAME} main.c kbin.c)