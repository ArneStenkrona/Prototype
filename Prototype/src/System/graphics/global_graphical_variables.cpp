#include "global_graphical_variables.h"

//Screen dimension constants
const int SCREEN_WIDTH = 2 * 512;
const int SCREEN_HEIGHT = 2 * 288;
const float SCALE_X = 2;
const float SCALE_Y = 2;

//Frame rate related
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


//The window renderer
SDL_Renderer* MAIN_GAME_RENDERER = NULL;

