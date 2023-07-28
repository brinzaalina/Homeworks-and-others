cmake_minimum_required(VERSION 3.19)
project(Exercise_4_Complex)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_4_Complex
        classes.cpp
        classes.h
        main.cpp)
