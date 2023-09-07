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

    SDL_DestroyRenderer(main_Renderer);
    main_Renderer = nullptr;

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

    main_Renderer = SDL_CreateRenderer(Window, -1, 0);
    if (main_Renderer == nullptr) {
        std::cerr << "Unable to init Renderer: " << SDL_GetError() << std::endl;
        return 1;
    }
    active = true;
    return 0;
}

void core::draw_window_border(u32 rgba) {
    u8 a = rgba & 0xff;
    u8 b = rgba >> 8 & 0xff;
    u8 g = rgba >> 16 & 0xff;
    u8 r = rgba >> 24 & 0xff;

    SDL_SetRenderDrawColor(main_Renderer, r, g, b, a);
    SDL_Rect border;
    border.x = 0, border.y = 0;
    border.h = window_h;
    border.w = window_w;
    SDL_RenderDrawRect(main_Renderer, &border);
}

void core::render() {
    SDL_SetRenderDrawColor(main_Renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(main_Renderer);

    draw_window_border(orange);

    SDL_RenderPresent(main_Renderer);
}

void core::event_handler() {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                active = false;
                break;
            default:
                break;
        }
    }
}

bool core::is_active() {
    return active;
}

