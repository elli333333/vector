//
// Created by ellie on 10/20/23.
//

#ifndef VECTOR_RENDERER_HPP
#define VECTOR_RENDERER_HPP

#include "common.hpp"

namespace vector {

    class renderer {
    private:
        u32 bg = vector::colour::black;
        u32 fg = vector::colour::white;
    public:
        renderer();
        ~renderer();

        u8 swap(std::shared_ptr<SDL_Surface *> front, std::shared_ptr<SDL_Surface *> back);
        u8 clear(std::shared_ptr<SDL_Surface *> &_surface);

        u8 set_fg(u32 colour);
        u8 set_bg(u32 colour);
    };

} // vector

#endif //VECTOR_RENDERER_HPP
