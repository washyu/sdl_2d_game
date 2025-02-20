#ifndef PLAYER_H
#define PLAYER_H

#include "../sprite/sprite.h"
#include "../sprite/AssetLoader.h"
#include "Direction.h"
#include "InputHandler.h"
#include <memory>
#include <unordered_map>
#include <string>

enum class PlayerState {
    IDLE,
    WALK,
    ATTACK1,
    ATTACK2,
    ATTACK3,
    HURT,
    DEATH
};

class Player {
    private:
        std::unordered_map<PlayerState, std::unique_ptr<Sprite>> animations;
        PlayerState currentState;
        PlayerState attackState;
        AssetLoader& assetLoader;

        Direction direction;
        int x, y;
        int scale;
        InputHandler& inputHandler;
        bool attackInProgress;
        
        void loadAnimation(PlayerState state, const std::string& path, int frameCount);
        void handleInput();

    public:
        Player(AssetLoader& assetLoader, InputHandler& inputHandler, int x, int y, int scale, Direction direction);
        void setDirection(Direction newDirection) { direction = newDirection; };
        void update();
        void render(SDL_Renderer* renderer);
        void setState(PlayerState newState);
        void setPosition(int newX, int newY);
        void setScale(int newScale);
};

#endif // PLAYER_H