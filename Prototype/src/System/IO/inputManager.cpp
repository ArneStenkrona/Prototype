#include "inputManager.h"
#include <iostream>
#include "System\graphics\graphicsEngine.h"

const Uint8* KeyboardState = SDL_GetKeyboardState(NULL);

//Keystates from last frame
bool lastKeyStates[NMBR];
//Keystates updated on keyPress
bool currentKeyStates[NMBR];

bool initializeInputManager() {

    updateCurrentKeys();

    return true;
}

bool getKeyDown(INPUT_KEYS key) {

    updateCurrentKeys();

    return !lastKeyStates[key] && currentKeyStates[key];

}

bool getKeyUp(INPUT_KEYS key) {


    updateCurrentKeys();

    return lastKeyStates[key] && !currentKeyStates[key];

}

bool getKey(INPUT_KEYS key) {

    updateCurrentKeys();

    return currentKeyStates[key];


}

void getMouseCoordinates(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

void updateCurrentKeys() {
    currentKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    currentKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    currentKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    currentKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    currentKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
    currentKeyStates[INPUT_KEY_R] = KeyboardState[SDL_SCANCODE_R];
    currentKeyStates[INPUT_KEY_F] = KeyboardState[SDL_SCANCODE_F];
    currentKeyStates[INPUT_KEY_G] = KeyboardState[SDL_SCANCODE_G];
    currentKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
    currentKeyStates[INPUT_KEY_LCTRL] = KeyboardState[SDL_SCANCODE_LCTRL];
    currentKeyStates[MOUSE_LEFT] = GraphicsEngine::getActiveWindow()->getLeftMouse();
    currentKeyStates[MOUSE_RIGHT] = GraphicsEngine::getActiveWindow()->getRightMouse();
}

void updateInputManager() {

    lastKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    lastKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    lastKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    lastKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    lastKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
    lastKeyStates[INPUT_KEY_R] = KeyboardState[SDL_SCANCODE_R];
    lastKeyStates[INPUT_KEY_F] = KeyboardState[SDL_SCANCODE_F];
    lastKeyStates[INPUT_KEY_G] = KeyboardState[SDL_SCANCODE_G];
    lastKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
    lastKeyStates[INPUT_KEY_LCTRL] = KeyboardState[SDL_SCANCODE_LCTRL];
    lastKeyStates[MOUSE_LEFT] = GraphicsEngine::getActiveWindow()->getLeftMouse();
    lastKeyStates[MOUSE_RIGHT] = GraphicsEngine::getActiveWindow()->getRightMouse();
    updateCurrentKeys();
}