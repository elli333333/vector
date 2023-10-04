#include "common.hpp"
#include "core.hpp"
#include "entity.hpp"


int main(int argc, char *argv[]) {

    std::unique_ptr<core> Game = std::make_unique<core>("test", 1280, 720);

    while(Game->is_active()) {
        Game->watchdog();
    }

    return 0;
}