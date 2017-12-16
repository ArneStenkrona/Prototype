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
#include "System/GUI/Window/lwindow.h"

//Right now this only initializes SDL stuff. 
//Ideally, resource managers should also be initalized here too.
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
    gameLoop();
    close();
    return 0;
}