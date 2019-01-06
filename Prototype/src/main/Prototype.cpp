// Prototype.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Prototype.h"
#include "../math/lTimer.h"
#include "../System/IO/inputManager.h"
#include "../System/Physics/physicsEngine.h"
#include "System\graphics\graphicsEngine.h"
#include "System\game\gameLogic.h"
#include "World\editor\editor.h"


bool init()
{
    return GraphicsEngine::initializeGraphicsEngine();
}

void close()
{
    GraphicsEngine::closeGraphicsEngine();
}

int main(int /* argc */, char * /* args */[])
{   
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
    }
    if (MessageBoxA(NULL, "Open editor?", "Choose mode", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDNO) {
        GameLogic::gameLoop();
    }
    else {
        Editor().run();
    }
    close();
    return 0;
}