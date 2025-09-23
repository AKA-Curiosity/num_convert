cmake_minimum_required(VERSION 4.0)
project(num_convert)

set(CMAKE_CXX_STANDARD 26)

add_executable(num_convert main.cpp
        converter.cpp
        converter.h)
