//
// Created by ellie on 10/20/23.
//

#include "renderer.hpp"

namespace vector {
    renderer::renderer() = default;

    renderer::~renderer() = default;

    u8 renderer::swap(std::shared_ptr<SDL_Surface*> front, std::shared_ptr<SDL_Surface*> back) {
        SDL_BlitSurface(*front, nullptr, *back, nullptr);
        return 0;
    }

    u8 renderer::clear(std::shared_ptr<SDL_Surface *> &_surface) {
        SDL_Surface* surface = *_surface;
        SDL_LockSurface(surface);
        SDL_memset(surface->pixels, 0xF, surface->h * surface->pitch);
        SDL_UnlockSurface(surface);
        *_surface = surface;
        return 0;
    }

    u8 renderer::set_fg(u32 colour) {
        fg = colour;
        return 0;
    }

    u8 renderer::set_bg(u32 colour) {
        bg = colour;
        return 0;
    }
} // vector