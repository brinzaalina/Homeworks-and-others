cmake_minimum_required(VERSION 3.19)
project(Exercise_1_Stack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_1_Stack
        main.cpp
        Stack.cpp
        Stack.h)
