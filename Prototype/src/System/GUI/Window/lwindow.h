/*
Wrapperclass for SDL windows
*/

#pragma once
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

class LWindow {
public:
    LWindow(int _screen_width, int _screen_height, 
           float _scale_x, float _scale_y);
    ~LWindow();

    //Has to be called in order for the window to be active
    void update();

    SDL_Renderer *getRenderer();

    //Returns true if window should be closed
    bool getExit();

private:
    SDL_Window* gWindow = NULL;
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    SDL_Renderer* windowRenderer;

    //Screen dimension constants
    const int screen_width;
    const int screen_height;
    const float scale_x;
    const float scale_y;

    SDL_Event e; 
    bool exit;
    //checks if user exists the window
    void pollExit();

    bool init();
    void close();




};