#include "Player.h"
#include <iostream>

Player::Player(AssetLoader& assetLoader, InputHandler& inputHandler, int x, int y, int scale, Direction direction)
    : assetLoader(assetLoader), inputHandler(inputHandler), x(x), y(y), currentState(PlayerState::IDLE), attackState(PlayerState::IDLE), scale(scale), direction(direction), attackInProgress(false) {
    
    loadAnimation(PlayerState::IDLE, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Idle.png", 6);
    loadAnimation(PlayerState::WALK, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Walk.png", 8);
    loadAnimation(PlayerState::ATTACK1, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Attack01.png", 6);
    loadAnimation(PlayerState::ATTACK2, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Attack02.png", 6);
    loadAnimation(PlayerState::ATTACK3, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Attack03.png", 9);
    loadAnimation(PlayerState::HURT, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Hurt.png", 4);
    loadAnimation(PlayerState::DEATH, "assets/Characters(100x100)/Soldier/Soldier with shadows/Soldier-Death.png", 4);

    for (auto& [state, sprite] : animations) {
        sprite->setScale(scale);
        sprite->setFrameDelay(10);
    }
}

void Player::loadAnimation(PlayerState state, const std::string& path, int frameCount) {
    animations[state] = std::make_unique<Sprite>(assetLoader, path, frameCount);
}

void Player::handleInput() {
    inputHandler.handleInput();

    if (inputHandler.isActionActive(Action::MOVE_LEFT)) {
        direction = Direction::LEFT;
        currentState = PlayerState::WALK;
        x -= 2;
        std::cout << "Moving left" << std::endl;
    } else if (inputHandler.isActionActive(Action::MOVE_RIGHT)) {
        direction = Direction::RIGHT;
        currentState = PlayerState::WALK;
        x += 2;
        std::cout << "Moving right" << std::endl;
    } else if (inputHandler.isActionActive(Action::MOVE_UP)) {
        currentState = PlayerState::WALK;
        direction = Direction::RIGHT;
        y -= 2;
        std::cout << "Moving up" << std::endl;
    } else if (inputHandler.isActionActive(Action::MOVE_DOWN)) {
        currentState = PlayerState::WALK;
        direction = Direction::LEFT;
        y += 2;
        std::cout << "Moving down" << std::endl;
    } else {
        currentState = PlayerState::IDLE;
    }

    if (inputHandler.isActionActive(Action::ATTACK)) {
        attackState = PlayerState::ATTACK1;
        attackInProgress = true;
    }
}

void Player::update() {
    handleInput();

    if (attackInProgress) {
        if (auto it = animations.find(attackState); it != animations.end()) {
            it->second->update();
            if (it->second->isAnimationComplete()) {
                attackInProgress = false;
                attackState = PlayerState::IDLE;
            }
        }
    } else {
        if (auto it = animations.find(currentState); it != animations.end()) {
            it->second->update();
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (attackInProgress) {
        if (auto it = animations.find(attackState); it != animations.end()) {
            it->second->render(renderer, x, y, direction);
        }
    } else {
        if (auto it = animations.find(currentState); it != animations.end()) {
            it->second->render(renderer, x, y, direction);
        }
    }
}

void Player::setState(PlayerState newState) {
    currentState = newState;
}

void Player::setPosition(int newX, int newY) {
    x = newX; 
    y = newY;
}

void Player::setScale(int newScale) {
    scale = newScale;
    for (auto& [state, sprite] : animations) {
        sprite->setScale(scale);
    }
}