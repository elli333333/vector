cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
include(vcpkg.cmake)
vcpkg_init()

project(vector)

find_package(fmt CONFIG REQUIRED)

add_executable(vector
        src/main.cpp
)


set_property(TARGET vector PROPERTY COMPILE_WARNING_AS_ERROR ON)

set(DEPENDS ;)
list(APPEND DEPENDS PRIVATE fmt::fmt)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        list(APPEND DEPENDS m)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
#    list(APPEND DEPENDS m)
endif ()

message(${DEPENDS})

target_link_libraries(vector
        ${DEPENDS}
        )