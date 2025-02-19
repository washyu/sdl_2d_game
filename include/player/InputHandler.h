#ifndef IMPUT_HANDLER_H
#define IMPUT_HANDLER_H

#include <SDL.h>
#include <unordered_map>
#include <functional>

enum class Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    ATTACK,
};

class InputHandler {
    public:
        InputHandler();
        void handleInput();
        bool isActionActive(Action action) const;
    private:
        std::unordered_map<SDL_Scancode, Action> keyBindings;
        std::unordered_map<Action, bool> actionStates;
};

#endif // IMPUT_HANDLER_H