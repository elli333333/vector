#include <iostream>
#include <memory>

// Local Headers
#include "core.hpp"


int main(int argc, char *argv[]) {

    std::unique_ptr<core> Game = std::make_unique<core>("test", 640, 480);

    while(Game->active) {
        Game->event_handler();
        Game->render();
    }

    return 0;
}