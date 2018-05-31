#include "inputManager.h"
#include <iostream>

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
    currentKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
}

void updateInputManager() {

    lastKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    lastKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    lastKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    lastKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    lastKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
    lastKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
    
    updateCurrentKeys();

}