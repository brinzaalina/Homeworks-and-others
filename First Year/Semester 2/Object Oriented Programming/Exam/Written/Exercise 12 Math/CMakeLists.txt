cmake_minimum_required(VERSION 3.19)
project(Exercise_12_Math)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_12_Math
        classes.cpp
        classes.h
        main.cpp)
