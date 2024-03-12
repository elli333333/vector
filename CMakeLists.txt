cmake_minimum_required(VERSION 3.18)
include(FetchContent)
project(vector)

set(CMAKE_CXX_STANDARD 20)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/Dependencies)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG ac13ca9ab691e13e8eebe9684740ddcb0d716203 # SDL 2.26.5
)

FetchContent_GetProperties(SDL2)
FetchContent_Populate(SDL2)

add_subdirectory(Dependencies/sdl2-src)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281 #{fmt} 10.2.1
)

FetchContent_GetProperties(fmt)
FetchContent_Populate(fmt)

add_subdirectory(Dependencies/fmt-src)

add_executable(vector
        src/main.cpp
        src/engine/common.hpp
        src/engine/renderer.cpp
        src/engine/renderer.hpp
        src/engine/core.cpp
        src/engine/core.hpp)

target_link_libraries(vector
        PRIVATE SDL2::SDL2-static
        PRIVATE fmt::fmt
        m
        )

target_compile_options(vector PRIVATE -Wall -Wextra -Wpedantic -Werror)