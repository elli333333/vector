//
// Created by ellie on 2/4/24.
//

#ifndef VECTOR_CORE_HPP
#define VECTOR_CORE_HPP

#include "common.hpp"
#include "renderer.hpp"

namespace vector {
    class core {
    private:
        std::unique_ptr<SDL_Window *> window = nullptr;

        std::shared_ptr<SDL_Surface *> front = nullptr;
        std::shared_ptr<SDL_Surface *> back = nullptr;

        void loop();

    public:
        explicit core(const std::string& window_title);
        ~core();

        std::unique_ptr<vector::renderer> renderer = nullptr;

    };
}

#endif //VECTOR_CORE_HPP
