//
// Created by ellie on 2/4/24.
//

#ifndef VECTOR_CORE_HPP
#define VECTOR_CORE_HPP

#include "common.hpp"

namespace vector {
    class core {
    private:
        SDL_Window *window = nullptr;
    public:
        core(std::string window_title);
    };
}

#endif //VECTOR_CORE_HPP
