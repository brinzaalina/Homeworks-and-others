cmake_minimum_required(VERSION 3.19)
project(Exercise_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_3
        classes.cpp
        classes.h
        main.cpp)
