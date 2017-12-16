#include "lwindow.h"

LWindow::LWindow(int _screen_width, int _screen_height, 
               float _scale_x, float _scale_y): windowRenderer(NULL), 
                                        screen_width(_screen_width), screen_height(_screen_height),
                                        scale_x(_scale_x), scale_y(_scale_y)
{
    if (!init()) {
        printf("Failed to initialize!\n");
    }
}

LWindow::~LWindow()
{
    close();
}

void LWindow::update()
{
    pollExit();
}

SDL_Renderer * LWindow::getRenderer()
{
    return windowRenderer;
}

bool LWindow::getExit()
{
    return exit;
}

void LWindow::pollExit()
{
    while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                exit = true;
            }
        }
}

bool LWindow::init()
{
    //Initializiation flag
    bool success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error; %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! DSL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
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