#include "Game.h"
#include <iostream>

namespace Game {

    Game::Game()
        : window(nullptr), renderer(nullptr), assetLoader(nullptr), inputHandler(nullptr), player(nullptr), currentState(GameState::TITLE), running(true), fadeAlpha(0) {}

    Game::~Game() {
        delete player;
        delete inputHandler;
        delete assetLoader;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Game::init() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        SDL_RenderSetLogicalSize(renderer, 800, 600);

        assetLoader = new AssetLoader(renderer);
        inputHandler = new InputHandler();
        player = new Player(*assetLoader, *inputHandler, 400, 300, 2, Direction::RIGHT);
        
        return true;
    }

    void Game::run() {
        while(running) {
            handleEvents();
            update();
            render();
            SDL_Delay(16); //60fps ish....
        }
    }

    void Game::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_l) {
                    changeState(GameState::DEATH);
                } else if (event.key.keysym.sym == SDLK_SPACE) {
                    if (currentState == GameState::TITLE) {
                        changeState(GameState::MAIN);
                    }
                }
            }
        }
    }

    void Game::update() {
        switch (currentState) {
            case GameState::TITLE:
                // Update title screen
                break;
            case GameState::MAIN:
                player->update();
                break;  
            case GameState::DEATH:
                player->setState(PlayerState::DEATH);
                player->update();
                if (fadeAlpha < 255) {
                    SDL_Delay(16);
                    fadeAlpha += 5;
                }
                break;
        }
    }

    void Game::render() {
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        SDL_RenderClear(renderer);

        switch (currentState) {
            case GameState::TITLE:
                // Render title screen
                break;
            case GameState::MAIN:
                player->render(renderer);
                break;
            case GameState::DEATH:
                player->render(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, fadeAlpha);
                SDL_Rect fadeRect = {0, 0, 800, 600};
                SDL_RenderFillRect(renderer, &fadeRect);
                break;
        }

        SDL_RenderPresent(renderer);
    }

    void Game::changeState(GameState newState) {
        currentState = newState;
        if (newState == GameState::DEATH) {
            fadeAlpha = 0;
        }
    }

} // namespace Game