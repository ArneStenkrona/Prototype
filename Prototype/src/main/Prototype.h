#pragma once
//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to. This is the main window of the game
//I've chose to keep it here, in the main source file. It might be suitable to move this to graphics.h some time.
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;