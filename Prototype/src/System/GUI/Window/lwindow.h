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
#include "System\graphics\lTexture.h"

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

    inline bool getMouseOver() const { return mouseOver; }

    inline SDL_Window* getSDLWindow() const { return gWindow; };

    inline bool getLeftMouse() const { return leftMouse; }
    inline bool getRightMouse() const { return rightMouse; }

    void clear();
    void present();

protected:
    int windowID;

    SDL_Window* gWindow;
    //The surface contained by the window
    SDL_Surface* gScreenSurface;

    SDL_Renderer* mRenderer;

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

    //mouse button being pressed
    bool leftMouse;
    bool rightMouse;

    bool exit;
    //checks if user exists the window
    void pollEvent(SDL_Event e);

    bool init();
    void close();

    SDL_GLContext context;
    unsigned int vertexArrayID;

    LTexture frameBuffer;

};