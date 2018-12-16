#include "lwindow.h"
#include "System\IO\inputManager.h"

LWindow::LWindow(int _screen_width, int _screen_height, 
               int _scale_x, int _scale_y): gWindow(NULL), mRenderer(NULL),
                                        screen_width(_screen_width), screen_height(_screen_height),
                                        scale_x(_scale_x), scale_y(_scale_y),
                                        mouseOver(false),
                                        vertexArrayID(0)
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
    SDL_DestroyWindow(gWindow);
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
    inputBuffer = "";
}

SDL_Renderer * LWindow::getRenderer()
{
    return mRenderer;
}
 
bool LWindow::hasExited()
{
    return exit;
}

void LWindow::getPos(int *x, int *y)
{
    SDL_GetWindowPosition(gWindow, x, y);
}

void LWindow::getDimensions(int * x, int * y)
{
    SDL_GetWindowSize(gWindow, x, y);
}

void LWindow::clear()
{
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);
}

void LWindow::present()
{
    SDL_SetRenderTarget(mRenderer, NULL);
    frameBuffer.render(0,0);
    SDL_RenderPresent(mRenderer);
    frameBuffer.setAsRenderTarget(mRenderer);
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
            switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button)
                {
                case SDL_BUTTON_LEFT:
                    leftMouse = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    rightMouse = true;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (e.button.button)
                {
                case SDL_BUTTON_LEFT:
                    leftMouse = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    rightMouse = false;
                    break;
                }
                break;
            case SDL_TEXTINPUT:
                inputBuffer = e.text.text;
                break;
            }
        }
}

bool LWindow::init()
{
    //Create window
    gWindow = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! DSL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create renderer for window
    mRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (mRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

        windowID = SDL_GetWindowID(gWindow);
    //Initialize renderer color
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Enable alpha in draw mode
    SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
    //Set render scale
    SDL_RenderSetScale(mRenderer, scale_x, scale_y);
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    frameBuffer.createBlank(screen_width, screen_height, mRenderer);
    frameBuffer.setAsRenderTarget(mRenderer);
    return true;
}

void LWindow::close()
{
    //Destroy window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    mRenderer = NULL;
}