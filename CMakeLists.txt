cmake_minimum_required(VERSION 3.18)
project(vector)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector
        src/main.cpp
        src/colour_utils.h src/core.cpp src/core.hpp)

target_link_libraries(vector
        m
        SDL2::SDL2)

#add_executable(fbtest
#        fbtest.c
#        colour_utils.h)
#
#target_link_libraries(fbtest m)