#pragma once
#include "SDL.h"
#include <string>

//Available keys
enum Input_key {
    INPUT_KEY_1,
    INPUT_KEY_2,
    INPUT_KEY_3,
    INPUT_KEY_4,
    INPUT_KEY_5,
    INPUT_KEY_6,
    INPUT_KEY_7,
    INPUT_KEY_8,
    INPUT_KEY_9,
    INPUT_KEY_0,
    INPUT_KEY_Q,
    INPUT_KEY_W,
    INPUT_KEY_E,
    INPUT_KEY_R,
    INPUT_KEY_T,
    INPUT_KEY_Y,
    INPUT_KEY_U,
    INPUT_KEY_I,
    INPUT_KEY_O,
    INPUT_KEY_P,
    INPUT_KEY_A,
    INPUT_KEY_S,
    INPUT_KEY_D,
    INPUT_KEY_F,
    INPUT_KEY_G,
    INPUT_KEY_H,
    INPUT_KEY_J,
    INPUT_KEY_K,
    INPUT_KEY_L,
    INPUT_KEY_Z,
    INPUT_KEY_X,
    INPUT_KEY_C,
    INPUT_KEY_V,
    INPUT_KEY_B,
    INPUT_KEY_N,
    INPUT_KEY_M,
    INPUT_KEY_SPACE,
    INPUT_KEY_BACKSPACE,
    INPUT_KEY_LSHIFT,
    INPUT_KEY_LCTRL,
    INPUT_KEY_KP_ENTER,
    INPUT_KEY_RETURN,
    INPUT_KEY_TAB,
    INPUT_KEY_KP_MINUS,
    INPUT_KEY_KP_PLUS,
    MOUSE_LEFT,
    MOUSE_RIGHT,
    NMBR
};

//Initalize the input manager
bool initializeInputManager();

//Update keystates in manager
void updateInputManager();
//Get the current keystates
void updateCurrentKeys();
//Returns true during the frame the user starts pressing down the key identified by name
bool getKeyDown(Input_key key);
//Returns true during the frame the user starts releases the key identified by name
bool getKeyUp(Input_key key);
//Returns true if key is currently pressed
bool getKey(Input_key key);
//Sets the referenced variables to mouse coordinates
void getMouseCoordinates(int& x, int& y);
//Sets the referenced variables to mouse world coordinates
//that is, considering scale of the window
void getMouseWorldCoordinates(int& x, int& y);

//Gets the input buffer from active window
std::string getInputBuffer();
//Edits the string according to inputs from active window
void modifyStringFromInput(std::string& s);

#pragma once
