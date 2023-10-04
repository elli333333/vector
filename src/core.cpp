//
// Created by ellie on 24/04/22.
//
#include "core.hpp"

core::core() {
    init("untitled", 640, 480);
}
core::core(const std::string& windowTitle, u16 x, u16 y) {
    init(windowTitle, x, y);
    window_w = x;
    window_h = y;
}

core::~core() {
    SDL_DestroyWindow(Window);
    Window = nullptr;

    event_mgr.join();
    render_thread.join();
    entity_mgr.join();

    SDL_Quit();
}

int core::init(const std::string& windowTitle, u16 x, u16 y) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    Window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);
    if (Window == nullptr) {
        std::cerr << "Unable to init Window: " << SDL_GetError() << std::endl;
        return 1;
    }

    main_Renderer = std::make_unique<SDL_Renderer*>(SDL_CreateRenderer(Window, -1, 0));
    if (main_Renderer == nullptr) {
        std::cerr << "Unable to init Renderer: " << SDL_GetError() << std::endl;
        return 1;
    }
    start_threads();
    active = true;
    return 0;
}

void core::draw_window_border(u32 rgba, SDL_Renderer *renderer) {
    set_colour(rgba, renderer);
    SDL_Rect border;
    border.x = 0, border.y = 0;
    border.h = window_h;
    border.w = window_w;
    SDL_RenderDrawRect(renderer, &border);
}

void core::render(std::unique_ptr<SDL_Renderer *> renderer) {
    std::cout << "render thread active\n";;

    while(active) {
        set_colour(pink, *renderer);
        SDL_RenderClear(*renderer);

        draw_window_border(orange, *renderer);

        SDL_RenderPresent(*renderer);
    }
    std::cout << "render thread joinable\n";
}

void core::event_handler() {
    std::cout << "event handler active\n";
    SDL_Event event;
    while(active) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                default:
                    break;
            }
        }
    }
    std::cout << "event handler joinable\n";

}

bool core::is_active() {
    return active;
}


// TODO
void core::entity_handler() {
}

void core::watchdog() {
    while(active) {

    }
}

void core::set_colour(u32 rgba, SDL_Renderer *renderer) {
        u8 a = rgba & 0xff;
        u8 b = rgba >> 8 & 0xff;
        u8 g = rgba >> 16 & 0xff;
        u8 r = rgba >> 24 & 0xff;

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
}


