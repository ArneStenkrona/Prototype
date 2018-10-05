#include "inputManager.h"
#include <iostream>
#include "System\graphics\graphicsEngine.h"

const Uint8* KeyboardState = SDL_GetKeyboardState(NULL);

//Keystates from last frame
bool lastKeyStates[SDL_NUM_SCANCODES];
//Keystates updated on keyPress
bool currentKeyStates[SDL_NUM_SCANCODES];

bool initializeInputManager() {

    updateCurrentKeys();

    return true;
}

bool getKeyDown(Input_key key) {

    updateCurrentKeys();

    return !lastKeyStates[key] && currentKeyStates[key];
}

bool getKeyUp(Input_key key) {


    updateCurrentKeys();

    return lastKeyStates[key] && !currentKeyStates[key];
}

bool getKey(Input_key key) {

    updateCurrentKeys();

    return currentKeyStates[key];
}

void getMouseCoordinates(int& x, int& y)
{
    SDL_GetMouseState(&x, &y);
}

void getMouseWorldCoordinates(int& x, int& y)
{
    SDL_GetMouseState(&x, &y);
    x /= GraphicsEngine::SCALE_X;
    y /= GraphicsEngine::SCALE_Y;
}

std::string getInputBuffer()
{
    return GraphicsEngine::getActiveWindow()->getInputBuffer();
}

void modifyStringFromInput(std::string & s)
{
    s += GraphicsEngine::getActiveWindow()->getInputBuffer();
    if (getKeyDown(INPUT_KEY_BACKSPACE) && !s.empty())
        s.pop_back();
}

void updateCurrentKeys() {
    currentKeyStates[INPUT_KEY_1] = KeyboardState[SDL_SCANCODE_1];
    currentKeyStates[INPUT_KEY_2] = KeyboardState[SDL_SCANCODE_2];
    currentKeyStates[INPUT_KEY_3] = KeyboardState[SDL_SCANCODE_3];
    currentKeyStates[INPUT_KEY_4] = KeyboardState[SDL_SCANCODE_4];
    currentKeyStates[INPUT_KEY_5] = KeyboardState[SDL_SCANCODE_5];
    currentKeyStates[INPUT_KEY_6] = KeyboardState[SDL_SCANCODE_6];
    currentKeyStates[INPUT_KEY_7] = KeyboardState[SDL_SCANCODE_7];
    currentKeyStates[INPUT_KEY_8] = KeyboardState[SDL_SCANCODE_8];
    currentKeyStates[INPUT_KEY_9] = KeyboardState[SDL_SCANCODE_9];
    currentKeyStates[INPUT_KEY_0] = KeyboardState[SDL_SCANCODE_0];
    currentKeyStates[INPUT_KEY_Q] = KeyboardState[SDL_SCANCODE_Q];
    currentKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    currentKeyStates[INPUT_KEY_E] = KeyboardState[SDL_SCANCODE_E];
    currentKeyStates[INPUT_KEY_R] = KeyboardState[SDL_SCANCODE_R];
    currentKeyStates[INPUT_KEY_T] = KeyboardState[SDL_SCANCODE_T];
    currentKeyStates[INPUT_KEY_Y] = KeyboardState[SDL_SCANCODE_Y];
    currentKeyStates[INPUT_KEY_U] = KeyboardState[SDL_SCANCODE_U];
    currentKeyStates[INPUT_KEY_I] = KeyboardState[SDL_SCANCODE_I];
    currentKeyStates[INPUT_KEY_O] = KeyboardState[SDL_SCANCODE_O];
    currentKeyStates[INPUT_KEY_P] = KeyboardState[SDL_SCANCODE_P];
    currentKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    currentKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    currentKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
    currentKeyStates[INPUT_KEY_F] = KeyboardState[SDL_SCANCODE_F];
    currentKeyStates[INPUT_KEY_G] = KeyboardState[SDL_SCANCODE_G];
    currentKeyStates[INPUT_KEY_H] = KeyboardState[SDL_SCANCODE_H];
    currentKeyStates[INPUT_KEY_J] = KeyboardState[SDL_SCANCODE_J];
    currentKeyStates[INPUT_KEY_K] = KeyboardState[SDL_SCANCODE_K];
    currentKeyStates[INPUT_KEY_L] = KeyboardState[SDL_SCANCODE_L];
    currentKeyStates[INPUT_KEY_Z] = KeyboardState[SDL_SCANCODE_Z];
    currentKeyStates[INPUT_KEY_X] = KeyboardState[SDL_SCANCODE_X];
    currentKeyStates[INPUT_KEY_C] = KeyboardState[SDL_SCANCODE_C];
    currentKeyStates[INPUT_KEY_V] = KeyboardState[SDL_SCANCODE_V];
    currentKeyStates[INPUT_KEY_B] = KeyboardState[SDL_SCANCODE_B];
    currentKeyStates[INPUT_KEY_N] = KeyboardState[SDL_SCANCODE_N];
    currentKeyStates[INPUT_KEY_M] = KeyboardState[SDL_SCANCODE_M];
    currentKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    currentKeyStates[INPUT_KEY_BACKSPACE] = KeyboardState[SDL_SCANCODE_BACKSPACE];
    currentKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
    currentKeyStates[INPUT_KEY_LCTRL] = KeyboardState[SDL_SCANCODE_LCTRL];
    currentKeyStates[MOUSE_LEFT] = GraphicsEngine::getActiveWindow()->getLeftMouse();
    currentKeyStates[MOUSE_RIGHT] = GraphicsEngine::getActiveWindow()->getRightMouse();
}

void updateInputManager() {

    lastKeyStates[INPUT_KEY_1] = KeyboardState[SDL_SCANCODE_1];
    lastKeyStates[INPUT_KEY_2] = KeyboardState[SDL_SCANCODE_2];
    lastKeyStates[INPUT_KEY_3] = KeyboardState[SDL_SCANCODE_3];
    lastKeyStates[INPUT_KEY_4] = KeyboardState[SDL_SCANCODE_4];
    lastKeyStates[INPUT_KEY_5] = KeyboardState[SDL_SCANCODE_5];
    lastKeyStates[INPUT_KEY_6] = KeyboardState[SDL_SCANCODE_6];
    lastKeyStates[INPUT_KEY_7] = KeyboardState[SDL_SCANCODE_7];
    lastKeyStates[INPUT_KEY_8] = KeyboardState[SDL_SCANCODE_8];
    lastKeyStates[INPUT_KEY_9] = KeyboardState[SDL_SCANCODE_9];
    lastKeyStates[INPUT_KEY_0] = KeyboardState[SDL_SCANCODE_0];
    lastKeyStates[INPUT_KEY_Q] = KeyboardState[SDL_SCANCODE_Q];
    lastKeyStates[INPUT_KEY_W] = KeyboardState[SDL_SCANCODE_W];
    lastKeyStates[INPUT_KEY_E] = KeyboardState[SDL_SCANCODE_E];
    lastKeyStates[INPUT_KEY_R] = KeyboardState[SDL_SCANCODE_R];
    lastKeyStates[INPUT_KEY_T] = KeyboardState[SDL_SCANCODE_T];
    lastKeyStates[INPUT_KEY_Y] = KeyboardState[SDL_SCANCODE_Y];
    lastKeyStates[INPUT_KEY_U] = KeyboardState[SDL_SCANCODE_U];
    lastKeyStates[INPUT_KEY_I] = KeyboardState[SDL_SCANCODE_I];
    lastKeyStates[INPUT_KEY_O] = KeyboardState[SDL_SCANCODE_O];
    lastKeyStates[INPUT_KEY_P] = KeyboardState[SDL_SCANCODE_P];
    lastKeyStates[INPUT_KEY_A] = KeyboardState[SDL_SCANCODE_A];
    lastKeyStates[INPUT_KEY_S] = KeyboardState[SDL_SCANCODE_S];
    lastKeyStates[INPUT_KEY_D] = KeyboardState[SDL_SCANCODE_D];
    lastKeyStates[INPUT_KEY_F] = KeyboardState[SDL_SCANCODE_F];
    lastKeyStates[INPUT_KEY_G] = KeyboardState[SDL_SCANCODE_G];
    lastKeyStates[INPUT_KEY_H] = KeyboardState[SDL_SCANCODE_H];
    lastKeyStates[INPUT_KEY_J] = KeyboardState[SDL_SCANCODE_J];
    lastKeyStates[INPUT_KEY_K] = KeyboardState[SDL_SCANCODE_K];
    lastKeyStates[INPUT_KEY_L] = KeyboardState[SDL_SCANCODE_L];
    lastKeyStates[INPUT_KEY_Z] = KeyboardState[SDL_SCANCODE_Z];
    lastKeyStates[INPUT_KEY_X] = KeyboardState[SDL_SCANCODE_X];
    lastKeyStates[INPUT_KEY_C] = KeyboardState[SDL_SCANCODE_C];
    lastKeyStates[INPUT_KEY_V] = KeyboardState[SDL_SCANCODE_V];
    lastKeyStates[INPUT_KEY_B] = KeyboardState[SDL_SCANCODE_B];
    lastKeyStates[INPUT_KEY_N] = KeyboardState[SDL_SCANCODE_N];
    lastKeyStates[INPUT_KEY_M] = KeyboardState[SDL_SCANCODE_M];
    lastKeyStates[INPUT_KEY_SPACE] = KeyboardState[SDL_SCANCODE_SPACE];
    lastKeyStates[INPUT_KEY_BACKSPACE] = KeyboardState[SDL_SCANCODE_BACKSPACE];
    lastKeyStates[INPUT_KEY_LSHIFT] = KeyboardState[SDL_SCANCODE_LSHIFT];
    lastKeyStates[INPUT_KEY_LCTRL] = KeyboardState[SDL_SCANCODE_LCTRL];
    lastKeyStates[MOUSE_LEFT] = GraphicsEngine::getActiveWindow()->getLeftMouse();
    lastKeyStates[MOUSE_RIGHT] = GraphicsEngine::getActiveWindow()->getRightMouse();
    updateCurrentKeys();
}