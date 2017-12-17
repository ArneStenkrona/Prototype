// Prototype.cpp : Defines the entry point for the console application.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Prototype.h"
#include "../math/lTimer.h"
#include "../System/graphics/global_graphical_variables.h"
#include "../System/IO/inputManager.h"
#include "../System/Physics/physicsEngine.h"
#include "System\game\gameLogic.h"
#include <Windows.h>
#include "World\editor\editor.h"


bool init()
{

    //Initializiation flag
    bool success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error; %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
   


    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
    }
    if (MessageBoxA(NULL, "Open editor?", "Choose mode", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDNO) {
        gameLoop();
    }
    else {
        Editor().run();
    }
    close();
    return 0;
}