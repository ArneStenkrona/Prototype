#pragma once
#include "System\graphics\graphicsEngine.h"
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace::std;
vector<set<Renderer*>> GraphicsEngine::renderQueue = vector<set<Renderer*>>();

//Screen dimension constants
const float GraphicsEngine::SCALE_X = 3;
const float GraphicsEngine::SCALE_Y = 3;
const int GraphicsEngine::SCREEN_WIDTH = GraphicsEngine::SCALE_X * 512;
const int GraphicsEngine::SCREEN_HEIGHT = GraphicsEngine::SCALE_Y * 288;
//Frame rate related
const int GraphicsEngine::SCREEN_FPS = 60;
const int GraphicsEngine::MICROSECONDS_PER_FRAME = 1000000 / SCREEN_FPS;
//game window
LWindow* GraphicsEngine::activeWindow = NULL;
//The window renderer
SDL_Renderer* GraphicsEngine::activeRenderer = NULL;

LTexture GraphicsEngine::frameBuffer = LTexture();

const bool GraphicsEngine::initSDL() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error; %s\n", SDL_GetError());
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_StartTextInput();

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

bool GraphicsEngine::initializeGraphicsEngine()
{
    return initSDL();
}

LWindow * GraphicsEngine::createGameWindow()
{
    delete(activeWindow);
    activeWindow = new LWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE_X, SCALE_Y);
    activeRenderer = activeWindow->getRenderer();
    return activeWindow;
}

EditorWindow * GraphicsEngine::createEditorWindow(Editor *editor)
{
    delete(activeWindow);
    EditorWindow* win = new EditorWindow(editor, SCREEN_WIDTH + (8 * Tile::TILE_SIZE * SCALE_X), 
                                         SCREEN_HEIGHT + (4 * Tile::TILE_SIZE * SCALE_Y), 
                                         SCALE_X, SCALE_Y, NULL);
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
    activeWindow->clear();
}

void GraphicsEngine::renderGraphics()
{
    for (vector<set<Renderer*>>::reverse_iterator i = renderQueue.rbegin();
        i != renderQueue.rend(); ++i) {
        for each (Renderer *r in (*i)) {
            r->render();
        }
    }
    activeWindow->present();
}


void GraphicsEngine::closeGraphicsEngine()
{
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}