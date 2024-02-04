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
#include <thread>
#include <functional>
#include <chrono>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/printf.h>

#include "SDL.h"

namespace vector {

    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t u8;

    typedef int64_t i64;
    typedef int32_t i32;
    typedef int16_t i16;
    typedef int8_t i8;


    typedef float_t f32;
    typedef double_t f64;

    typedef std::pair<f32, f32> f_coord;
    typedef std::pair<i32, i32> i_coord;

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

    void print_error(){
        auto const t = std::chrono::system_clock::now();
        fmt::print(stderr, fg(fmt::color::red),"[{:%T}] - Error: {}", t, SDL_GetError());
    }
}
#endif //VECTOR_COMMON_HPP
