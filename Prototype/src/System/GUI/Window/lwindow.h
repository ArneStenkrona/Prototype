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
           int _scale_x, int _scale_y);
    ~LWindow();

    //Updates all windows
    static void updateAll();

    virtual void update();

    SDL_Renderer *getRenderer();

    //Returns true if window should be closed
    bool hasExited();

    bool getMouseOver();

    bool popClickQueue();

protected:
    int windowID;

    SDL_Window* gWindow;
    //The surface contained by the window
    SDL_Surface* gScreenSurface;

    SDL_Renderer* windowRenderer;

    //Screen dimension constants, though I might remove this if I set window to resizable
    const int screen_width;
    const int screen_height;
    const int scale_x;
    const int scale_y;

    //Sets referenced variables to window coordinates
    void getPos(int *x, int *y);
    //Sets referenced variables to window dimensions
    void getDimensions(int *x, int *y);

    static list<LWindow*> all_windows;

private:
    //mouse is over window
    bool mouseOver;

    bool exit;
    //checks if user exists the window
    void pollEvent(SDL_Event e);

    bool init();
    void close();
    //queue for mouse clicks. Might expand this to other events
    list<bool> clickQueue;
};