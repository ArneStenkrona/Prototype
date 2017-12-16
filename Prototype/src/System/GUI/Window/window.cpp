#include "window.h"

Window::Window(int screen_width, int screen_height, 
               float scale_x, float scale_y, 
               int fps, int fps_ticks): RENDERER(NULL), 
                                        SCREEN_WIDTH(screen_width), SCREEN_HEIGHT(screen_height),
                                        SCALE_X(scale_x), SCALE_Y(scale_y),
                                        SCREEN_FPS(fps), SCREEN_TICK_PER_FRAME(fps_ticks)
{
    init();
}

Window::~Window()
{
    close();
}

void Window::update()
{
    pollExit();
}

void Window::pollExit()
{
    while (SDL_PollEvent(&e) != 0) {

        //User requests quit
        if (e.type == SDL_QUIT)
        {
            exit = true;
        }

    }

}

bool Window::init()
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
        gWindow = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! DSL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            RENDERER = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (RENDERER == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
                //Set render scale
                SDL_RenderSetScale(RENDERER, SCALE_X, SCALE_Y);
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

void Window::close()
{
    //Destroy window
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    RENDERER = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}