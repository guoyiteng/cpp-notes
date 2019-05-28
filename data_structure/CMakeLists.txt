cmake_minimum_required(VERSION 3.14)
project(data_structure)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

add_executable(data_structure
        src/main.cpp src/hashtable.h)
