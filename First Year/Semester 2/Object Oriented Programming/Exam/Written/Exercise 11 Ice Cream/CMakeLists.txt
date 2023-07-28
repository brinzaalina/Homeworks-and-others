cmake_minimum_required(VERSION 3.19)
project(Exercise_11_Ice_Cream)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_11_Ice_Cream
        classes.cpp
        classes.h
        main.cpp)
