cmake_minimum_required(VERSION 3.2)
project(labs-ap VERSION 0.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(WIN32)
    message(FATAL_ERROR "This is not meant for WINDOWS users((")
endif(WIN32)

message(STATUS "Adding subdirectories")
add_subdirectory("11-symbolic-data")
add_subdirectory("12-string-cxx")
add_subdirectory("13-text-files-c")
add_subdirectory("14-struct-binaries-c")
add_subdirectory("15-files-cxx")
add_subdirectory("16-cpu-directives")
message(STATUS "Adding subdirectories - done")