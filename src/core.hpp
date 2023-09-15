//
// Created by ellie on 24/04/22.
//

#ifndef VECTOR_CORE_HPP
#define VECTOR_CORE_HPP

#include "common.hpp"


class core {
private:
    SDL_Window *Window = nullptr;
    SDL_Renderer *main_Renderer = nullptr;

    int window_w = 0, window_h = 0;

    std::thread event_mgr = std::thread(&core::event_handler, this);
    std::thread render_thread = std::thread(&core::render, this);
    std::thread entity_mgr = std::thread(&core::event_handler, this);

    int init(const std::string& windowTitle, uint16_t x, uint16_t y);
    void draw_window_border(uint32_t rgba);

    std::atomic<bool> active = false;
public:
    core();
    core(const std::string& windowTitle, uint16_t x, uint16_t y);

    ~core();

    bool is_active();

    void render();
    void event_handler();

    [[maybe_unused]] void entity_handler();
};


#endif //VECTOR_CORE_HPP
