//
// Created by ellie on 24/04/22.
//

#ifndef VECTOR_CORE_HPP
#define VECTOR_CORE_HPP

#include "common.hpp"


class core {
private:
    SDL_Window *Window = nullptr;

    std::unique_ptr<SDL_Renderer*> main_Renderer = nullptr;

    int window_w = 0, window_h = 0;

    int init(const std::string& windowTitle, u16 x, u16 y);
    void draw_window_border(u32 rgba, SDL_Renderer *renderer);

    std::atomic<bool> active = false;

    std::thread event_mgr;
    std::thread render_thread;
    std::thread entity_mgr;

    void start_threads() {
        event_mgr = std::thread(&core::event_handler, this);
        render_thread = std::thread(&core::render, this, std::move(main_Renderer));
        entity_mgr = std::thread(&core::entity_handler, this);
    }
public:
    core();
    core(const std::string& windowTitle, uint16_t x, uint16_t y);

    ~core();

    bool is_active();

    void render(std::unique_ptr<SDL_Renderer *> renderer);
    void event_handler();
    void entity_handler();

    void watchdog();
};


#endif //VECTOR_CORE_HPP
