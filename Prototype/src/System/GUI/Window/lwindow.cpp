#include "lwindow.h"

LWindow::LWindow(int _screen_width, int _screen_height, 
               float _scale_x, float _scale_y): windowRenderer(NULL),
                                        screen_width(_screen_width), screen_height(_screen_height),
                                        scale_x(_scale_x), scale_y(_scale_y)
{
    if (!init()) {
        printf("Failed to initialize!\n");
    }

    all_windows.push_back(this);
}

LWindow::~LWindow()
{
    close();
    all_windows.remove(this);
}

list<LWindow*> LWindow::all_windows = list<LWindow*>();

void LWindow::update()
{
    for each (LWindow *w in all_windows) {
        w->pollEvent();
    }
}

SDL_Renderer * LWindow::getRenderer()
{
    return windowRenderer;
}

bool LWindow::getExit()
{
    return exit;
}

void LWindow::pollEvent()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_WINDOWEVENT && e.window.windowID == windowID)
        {
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                exit = true;
                break;

            }
        }
    }
}

bool LWindow::init()
{
    //Initializiation flag
    bool success = true;
        //Create window
        gWindow = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! DSL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            windowID = SDL_GetWindowID(gWindow);
            //Create renderer for window
            windowRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (windowRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Set render scale
                SDL_RenderSetScale(windowRenderer, scale_x, scale_y);
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    return success;
}

void LWindow::close()
{
    //Destroy window
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    windowRenderer = NULL;
}