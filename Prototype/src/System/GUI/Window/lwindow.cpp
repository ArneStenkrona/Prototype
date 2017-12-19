#include "lwindow.h"
#include "System\graphics\global_graphical_variables.h"
#include "System\IO\inputManager.h"

LWindow::LWindow(int _screen_width, int _screen_height, 
               int _scale_x, int _scale_y): gWindow(NULL), windowRenderer(NULL),
                                        screen_width(_screen_width), screen_height(_screen_height),
                                        scale_x(_scale_x), scale_y(_scale_y),
                                        mouseOver(false), clickQueue(list<bool>())
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

void LWindow::updateAll()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        for each (LWindow *w in all_windows) {
            w->pollEvent(e);
        }
    }
    for each (LWindow *w in all_windows) {
        w->update();
    }
}

void LWindow::update()
{
}

SDL_Renderer * LWindow::getRenderer()
{
    return windowRenderer;
}
 
bool LWindow::hasExited()
{
    return exit;
}

bool LWindow::getMouseOver()
{
    return mouseOver;
}

void LWindow::getPos(int *x, int *y)
{
    SDL_GetWindowPosition(gWindow, x, y);
}

void LWindow::getDimensions(int * x, int * y)
{
    SDL_GetWindowSize(gWindow, x, y);
}

bool LWindow::popClickQueue()
{

    bool res;

    if (clickQueue.size() != 0) {
        res = clickQueue.front();
        clickQueue.pop_front();
    }
    else {
        res = false;
    }

    return res;
}

void LWindow::pollEvent(SDL_Event e)
{
        if (e.type == SDL_WINDOWEVENT && e.window.windowID == windowID)
        {
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                exit = true;
                break;
                //Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
                mouseOver = true;
                break;

                //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
                mouseOver = false;
                break;
            }
        }
        else {
            switch (e.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                clickQueue.push_back(true);
                break;
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
            //Create renderer for window
            windowRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (windowRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                windowID = SDL_GetWindowID(gWindow);
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

        ACTIVE_RENDERER = windowRenderer;
    
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