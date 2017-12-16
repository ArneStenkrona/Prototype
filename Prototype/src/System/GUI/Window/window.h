/*
Baseclass for windows
*/

#pragma once
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

class Window {
public:
    Window(int screen_width, int screen_height, 
           float scale_x, float scale_y, 
           int fps, int fps_ticks);
    ~Window();

    //Has to be called in order for the window to be active
    void update();
private:
    SDL_Window* gWindow = NULL;
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    SDL_Renderer* RENDERER;

    //Screen dimension constants
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const float SCALE_X;
    const float SCALE_Y;

    //Frame rate related
    const int SCREEN_FPS;
    const int SCREEN_TICK_PER_FRAME;

    SDL_Event e; 
    bool exit;
    //checks if user exists the window
    void pollExit();

    bool init();
    void close();




};