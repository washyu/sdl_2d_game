#include "InputHandler.h"

InputHandler::InputHandler() {
    // Default key bindings
    keyBindings[SDL_SCANCODE_A] = Action::MOVE_LEFT;
    keyBindings[SDL_SCANCODE_D] = Action::MOVE_RIGHT;
    keyBindings[SDL_SCANCODE_W] = Action::MOVE_UP;
    keyBindings[SDL_SCANCODE_S] = Action::MOVE_DOWN;
    keyBindings[SDL_SCANCODE_SPACE] = Action::ATTACK;
}

void InputHandler::handleInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    for (auto& [key, action] : keyBindings) {
        actionStates[action] = state[key];
    }
}

bool InputHandler::isActionActive(Action action) const {
    auto it = actionStates.find(action);
    return actionStates.at(action);
}