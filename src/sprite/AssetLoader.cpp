#include "AssetLoader.h"

AssetLoader::AssetLoader(SDL_Renderer* renderer) : renderer(renderer) {}
    
SDL_Texture* AssetLoader::loadTexture(const std::string& path) {
    SDL_Texture* texture = nullptr;
    try {
        texture = IMG_LoadTexture(renderer, path.c_str());
        if (texture == nullptr) {
            throw std::runtime_error("Failed to load texture: " + std::string(IMG_GetError()));
        }
    } catch (const std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Exception: %s", e.what());
    }
    return texture;
}
