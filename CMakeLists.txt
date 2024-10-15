cmake_minimum_required(VERSION 3.18)
include(FetchContent)
project(vector)

set(CMAKE_CXX_STANDARD 20)

set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/Dependencies)


if (NOT TARGET SDL2)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG 79ec168f3c1e2fe27335cb8886439f7ef676fb49 # SDL 2.30.8
)

FetchContent_GetProperties(SDL2)
FetchContent_MakeAvailable(SDL2)
endif ()

add_subdirectory(Dependencies/sdl2-src)

if (NOT TARGET fmt)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 0c9fce2ffefecfdce794e1859584e25877b7b592 #{fmt} 11.0.2
)

FetchContent_GetProperties(fmt)
FetchContent_MakeAvailable(fmt)
endif ()

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