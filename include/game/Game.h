#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "../player/Player.h"
#include "../player/InputHandler.h"
#include "GameState.h"

namespace Game {

    class Game {
    public:
        Game();
        ~Game();
        bool init();
        void run();
        void handleEvents();
        void update();
        void render();
        void changeState(GameState newState);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        AssetLoader* assetLoader;
        InputHandler* inputHandler;
        Player* player;
        GameState currentState;
        bool running;
        Uint8 fadeAlpha;
    };

} // namespace Game

#endif // GAME_H