cmake_minimum_required(VERSION 3.22)
project(p3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p3
        kdtree.hpp
        main.cpp)
