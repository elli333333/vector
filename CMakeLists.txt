cmake_minimum_required(VERSION 3.18)
set(ENV{VCPKG_ROOT} [])
set(CMAKE_TOOLCHAIN_FILE )
project(vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector
        src/main.cpp
)

target_link_libraries(vector
#        PRIVATE SDL2::SDL2-static
#        PRIVATE fmt::fmt
#        m
        )

target_compile_options(vector PRIVATE)# -Wall -Wextra -Wpedantic -Werror)