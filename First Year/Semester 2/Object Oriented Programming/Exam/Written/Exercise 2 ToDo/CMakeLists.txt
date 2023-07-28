cmake_minimum_required(VERSION 3.19)
project(Exercise_2_ToDo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Exercise_2_ToDo
        clases.cpp
        clases.h
        main.cpp)
