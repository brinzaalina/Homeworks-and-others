cmake_minimum_required(VERSION 3.19)
project(Exercise_10_Channels)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_10_Channels
        classes.cpp
        classes.h
        main.cpp)
