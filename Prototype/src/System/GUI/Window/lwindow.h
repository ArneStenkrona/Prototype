/*
Wrapperclass for SDL_Window
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <list>

using namespace::std;

class LWindow {
public:
    LWindow(int _screen_width, int _screen_height, 
           float _scale_x, float _scale_y);
    ~LWindow();

    //Updates all windows
    static void update();

    SDL_Renderer *getRenderer();

    //Returns true if window should be closed
    bool hasExited();

private:
    int windowID;

    SDL_Window* gWindow;
    //The surface contained by the window
    SDL_Surface* gScreenSurface;

    SDL_Renderer* windowRenderer;

    static list<LWindow*> all_windows;

    //Screen dimension constants
    const int screen_width;
    const int screen_height;
    const float scale_x;
    const float scale_y;

    bool exit;
    //checks if user exists the window
    void pollEvent(SDL_Event e);

    bool init();
    void close();
    



};