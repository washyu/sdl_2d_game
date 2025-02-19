#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdexcept>

class AssetLoader {
        SDL_Renderer* renderer;
    public:
        AssetLoader(SDL_Renderer* renderer);
        SDL_Texture* loadTexture(const std::string& path);
};
