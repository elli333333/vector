#include <iostream>
#include <memory>

// Local Headers
#include "core.hpp"


int main(int argc, char *argv[]) {

    std::unique_ptr<core> Game = std::make_unique<core>("test", 1280, 720);

    while(Game->is_active()) {
        Game->event_handler();
        Game->render();
    }

    return 0;
}