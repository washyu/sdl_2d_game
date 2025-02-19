#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include "AssetLoader.h" 
#include "../player/Direction.h"

class Sprite { 
    private:
        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;
        int currentFrame;
        int frameCount;
        int frameDelay;
        int frameTimer;
        int scale;
    public:
        Sprite(AssetLoader& assetLoader, const std::string& path, int frameCount);
        ~Sprite();

        void update();
        void render(SDL_Renderer* renderer, int x, int y, Direction direction);
        void setScale(int newScale) { scale = newScale; }
        bool isLoaded() const { return texture != nullptr; } 
        void setFrameDelay(int delay) { frameDelay = delay;}
        bool isAnimationComplete() const {
            return currentFrame == frameCount - 1 && frameTimer == 0;
        }

};
#endif // SPRITE_H