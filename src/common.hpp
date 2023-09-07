//
// Created by ellie on 9/7/23.
//

#ifndef VECTOR_COMMON_HPP
#define VECTOR_COMMON_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <iostream>
#include <atomic>

#include "SDL.h"


typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

enum colour {
    red = 0xFF0000FF,
    green = 0x00FF00FF,
    blue = 0x0000FFFF,
    black = 0x111111FF,
    white = 0xaaaaaaFF,
    yellow = 0xFFFF00FF,
    magenta = 0xFF00FFFF,
    pink = 0xfc05caff,
    purple = 0x9505fcff,
    orange = 0xfc8405ff,

};

#endif //VECTOR_COMMON_HPP
