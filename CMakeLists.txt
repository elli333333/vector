cmake_minimum_required(VERSION 3.18)
project(vector)

find_package(SDL2)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector
        main.cpp)

target_link_libraries(vector
        m
        sdl2)

#add_executable(fbtest
#        fbtest.c
#        colour_utils.h)
#
#target_link_libraries(fbtest m)