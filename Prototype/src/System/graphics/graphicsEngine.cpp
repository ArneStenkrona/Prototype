#pragma once
#include "System\graphics\graphicsEngine.h"
#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "opengl\indexBuffer.h"
#include "opengl\vertexBuffer.h"
#include "opengl\shaderGL.h"
#include "opengl\vertexArray.h"
#include "opengl\rendererGL.h"
#include "opengl\vertexBufferLayout.h"
#include "opengl\textureGL.h"
#include "World\editor\editor.h"

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

LTexture GraphicsEngine::frameBuffer = LTexture();

const bool GraphicsEngine::initSDL() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error; %s\n", SDL_GetError());
        return false;
    }
    return true;
}

const bool GraphicsEngine::initOpenGL() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}

void GraphicsEngine::experimentGL()
{
    ShaderGL sh("Assets/shaders/TextureShader.shader");
    sh.bind();

    TextureGL texture("Assets/Concept Art/prototype title screen.png", 1);
    texture.bind();
    sh.setUniform1i("u_Texture", 1);

    RendererGL renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //Element
    float positions[] = { 
        -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f
    };

    unsigned int indices[] = { 
        0, 1, 2, 
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    //End element    

    while (true) {
        renderer.clear();
        renderer.draw(va, ib, sh);
        renderer.present();
        SDL_GL_SwapWindow(activeWindow->getSDLWindow());
    }
}

bool GraphicsEngine::initializeGraphicsEngine()
{

    return initSDL();// && initOpenGL();
}

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