cmake_minimum_required(VERSION 3.18)
include(FetchContent)
project(vector)

set(CMAKE_CXX_STANDARD 20)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/SDL)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG ac13ca9ab691e13e8eebe9684740ddcb0d716203 # SDL 2.26.5
)

FetchContent_GetProperties(SDL2)
FetchContent_Populate(SDL2)

add_subdirectory(SDL/sdl2-src)

add_executable(vector
        src/main.cpp
        src/colour_utils.h
        src/core.cpp
        src/core.hpp
        src/entity.cpp
        src/entity.hpp
        src/engine/common.hpp
        src/engine/renderer.cpp
        src/engine/renderer.hpp
        src/engine/vec2.cpp
        src/engine/vec2.hpp)

target_link_libraries(vector
        PRIVATE SDL2::SDL2-static
        m
        )

#add_executable(fbtest
#        fbtest.c
#        colour_utils.h)
#
#target_link_libraries(fbtest m)