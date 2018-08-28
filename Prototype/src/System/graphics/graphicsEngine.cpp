#pragma once
#include "System\graphics\graphicsEngine.h"
#include <vector>

using namespace::std;
vector<set<Renderer*>> GraphicsEngine::renderQueue = vector<set<Renderer*>>();

//Screen dimension constants
const int GraphicsEngine::SCREEN_WIDTH = 2 * 512;
const int GraphicsEngine::SCREEN_HEIGHT = 2 * 288;
const float GraphicsEngine::SCALE_X = 2;
const float GraphicsEngine::SCALE_Y = 2;
//Frame rate related
const int GraphicsEngine::SCREEN_FPS = 60;
const int GraphicsEngine::SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
//game window
LWindow* GraphicsEngine::activeWindow = NULL;
//The window renderer
SDL_Renderer* GraphicsEngine::activeRenderer = NULL;


LWindow * GraphicsEngine::createGameWindow()
{
    delete(activeWindow);
    activeWindow = new LWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE_X, SCALE_Y);
    activeRenderer = activeWindow->getRenderer();
    return activeWindow;
}

EditorWindow * GraphicsEngine::createEditorWindow()
{
    delete(activeWindow);
    EditorWindow* win = new EditorWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE_X, SCALE_Y, NULL);
    activeWindow = win;
    activeRenderer = activeWindow->getRenderer();
    return win;
}

void GraphicsEngine::addToRenderQueue(Renderer *r, int layer) {
    if (renderQueue.size() < layer + 1) renderQueue.resize(layer + 1);
    renderQueue[layer].insert(r);
}

void GraphicsEngine::removeFromRenderQueue(Renderer * r, int layer)
{
    if (renderQueue.size() > layer)
        renderQueue[layer].erase(r);
}

SDL_Renderer * GraphicsEngine::getActiveRenderer()
{
    return activeRenderer;
}

void GraphicsEngine::clearWindow()
{
    SDL_SetRenderDrawColor(activeWindow->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(activeWindow->getRenderer());
}

void GraphicsEngine::renderGraphics()
{
    for (vector<set<Renderer*>>::reverse_iterator i = renderQueue.rbegin();
        i != renderQueue.rend(); ++i) {
        for each (Renderer *r in (*i)) {
            r->render();
        }
    }
    SDL_RenderPresent(activeWindow->getRenderer());
}

bool GraphicsEngine::initializeGraphicsEngine()
{
    //Initializiation flag
    bool success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error; %s\n", SDL_GetError());
        success = false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return success;
}

void GraphicsEngine::closeGraphicsEngine()
{
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
