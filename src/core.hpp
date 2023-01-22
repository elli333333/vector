//
// Created by ellie on 24/04/22.
//

#ifndef VECTOR_CORE_HPP
#define VECTOR_CORE_HPP

#include <string>
#include <memory>
#include <iostream>
#include <atomic>

#include "SDL.h"

class core {
private:
    SDL_Window* Window = nullptr;
    SDL_Renderer* main_Renderer = nullptr;

    int init(const std::string& windowTitle, uint16_t x, uint16_t y);

public:
    core();
    core(const std::string& windowTitle, uint16_t x, uint16_t y);
    ~core();
    std::atomic<bool> active = false;

    void render();
    void event_handler();
};


#endif //VECTOR_CORE_HPP
