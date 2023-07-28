cmake_minimum_required(VERSION 3.19)
project(Exercise_7_Sale)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_7_Sale
        classes.cpp
        classes.h
        main.cpp)
