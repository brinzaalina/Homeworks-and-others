cmake_minimum_required(VERSION 3.19)
project(Exercise_5_Menu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_5_Menu
        classes.cpp
        classes.h
        main.cpp)
