#include <iostream>
#include "sprite.h"


Sprite::Sprite(AssetLoader& assetLoader, const std::string& path, int frameCount)
    : currentFrame(0), frameCount(frameCount), frameDelay(100), frameTimer(0), scale(1) {

    texture = assetLoader.loadTexture(path);
    if (!texture) {
        std::cout << "Failed to load image from" << path << std::endl;
        return;
    }
    
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    std::cout << "Texture loaded: " << path << " (" << textureWidth << "x" << textureHeight << ")" << std::endl;
    
    int frameWidth = textureWidth / frameCount;

    // Set up the source rectangle for the first frame
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = frameWidth;
    srcRect.h = textureHeight;

    // Set up destination rectangle    
    destRect.w = frameWidth * scale;
    destRect.h = textureHeight * scale;

    std::cout << "Frame dimensions: " << frameWidth << "x" << textureHeight << std::endl;
}

Sprite::~Sprite() {
    if(texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::update() {
    frameTimer++;
    if (frameTimer > frameDelay) {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % frameCount;
        srcRect.x = currentFrame * srcRect.w;
    }
}

void Sprite::render(SDL_Renderer* renderer, int x, int y, Direction direction) {
    if (!texture) {
        std::cout << "Attempting to render null texture" << std::endl;
        return;
    }

    destRect.x = x;
    destRect.y = y;
    destRect.w = srcRect.w * scale;
    destRect.h = srcRect.h * scale;

    //std::cout << "Rendering frame " << currentFrame << " at (" << x << "," << y 
    //          << ") size: " << destRect.w << "x" << destRect.h
    //          << " scale: " << scale << std::endl;
    if (direction == Direction::LEFT) {
        SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }
}

