//
// Created by ellie on 2/4/24.
//

#include "core.hpp"
namespace vector {
    core::core(std::string window_title) {
        if(!SDL_Init(SDL_INIT_VIDEO)) {
            vector::print_error();
        }
    }
}