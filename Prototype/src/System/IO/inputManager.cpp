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

void pollExit(SDL_Event & e, bool &exit)
{
    while (SDL_PollEvent(&e) != 0) {

        //User requests quit
        if (e.type == SDL_QUIT)
        {
            exit = true;
        }

    }

}

void updateCurrentKeys() {
    currentKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    currentKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    currentKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    currentKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    currentKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
}

void updateInputManager() {

    lastKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    lastKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    lastKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    lastKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    lastKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];

    updateCurrentKeys();

}