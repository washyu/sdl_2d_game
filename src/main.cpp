#include "game/Game.h"

int main(int argc, char* argv[]) {
    Game::Game game;
    if (!game.init()) {
        return 1;
    }
    game.run();
    return 0;
}