#pragma once
#include "SDL.h"

//Available keys
enum INPUT_KEYS {
    INPUT_KEY_W,
    INPUT_KEY_A,
    INPUT_KEY_S,
    INPUT_KEY_D,
    INPUT_KEY_SPACE,
    NMBR
};

//Initalize the input manager
bool initializeInputManager();

//Update keystates in manager
void updateInputManager();
//Get the current keystates
void updateCurrentKeys();
//Returns true during the frame the user starts pressing down the key identified by name
bool getKeyDown(INPUT_KEYS key);
//Returns true during the frame the user starts releases the key identified by name
bool getKeyUp(INPUT_KEYS key);
//Returns true if key is currently pressed
bool getKey(INPUT_KEYS key);
//Polls exit application action
void pollExit(SDL_Event &e, bool & exit);

#pragma once