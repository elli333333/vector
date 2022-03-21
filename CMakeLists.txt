cmake_minimum_required(VERSION 3.22)
project(vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector main.cpp)
target_link_libraries(vector -static)

add_executable(fbtest fbtest.c)
target_link_libraries(fbtest -static)