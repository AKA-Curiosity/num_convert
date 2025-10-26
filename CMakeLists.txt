cmake_minimum_required(VERSION 3.30.2)
project(num_convert)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(num_convert
    main.cpp
    converter.cpp
)
