//
// Created by ellie on 2/4/24.
//

#include "core.hpp"
namespace vector {
    core::core(const std::string& window_title) {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            vector::print_SDL_error();
            this->~core();
        }
        u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
        window = std::make_unique<SDL_Window *>(SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, window_flags));;
        u8 tries = 0;
        RETRY:
        if ((window == nullptr) && (tries < 2)) {
            window = std::make_unique<SDL_Window *>(SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, window_flags));
            ++tries;
            goto RETRY;
        }
        else if ((window == nullptr) && (tries >= 2)) {
            vector::print_SDL_error();
            this->~core();
        }

        front = std::make_shared<SDL_Surface *>(SDL_GetWindowSurface(*window));
        back = std::make_shared<SDL_Surface *>(SDL_GetWindowSurface(*window));

        renderer->clear(back);

        SDL_Surface* surface = *front;
        SDL_LockSurface(surface);
        SDL_memset(surface->pixels, 0x0, surface->h * surface->pitch);
        SDL_UnlockSurface(surface);
        *front = surface;

        renderer->swap(front, back);

        this->loop();
    }

    core::~core() {
//        SDL_DestroyWindow(*window);
        window = nullptr;

        SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        SDL_Quit();
    }

    void core::loop() {
       pause();
    }
}