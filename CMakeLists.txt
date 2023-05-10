cmake_minimum_required(VERSION 3.18)
project(vector)

set(CMAKE_CXX_STANDARD 20)



add_executable(vector
        src/main.cpp
        src/colour_utils.h src/core.cpp src/core.hpp)

target_link_libraries(vector
        PRIVATE SDL3::SDL3-static
        m
        )

#add_executable(fbtest
#        fbtest.c
#        colour_utils.h)
#
#target_link_libraries(fbtest m)