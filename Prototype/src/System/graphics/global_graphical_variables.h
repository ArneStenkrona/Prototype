#pragma once
#include "SDL_image.h"
//Global graphical variables. Might wanna rethink this design choice. Or not. I don't know yet

//Main renderer in game. 
extern SDL_Renderer* ACTIVE_RENDERER;

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const float SCALE_X;
extern const float SCALE_Y;

//Frame rate related
extern const int SCREEN_FPS;
extern const int SCREEN_TICK_PER_FRAME;

