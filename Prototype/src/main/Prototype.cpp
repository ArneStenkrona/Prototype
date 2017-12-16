// Prototype.cpp : Defines the entry point for the console application.
//
#include <SDL.h>
#undef main
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
            ACTIVE_RENDERER = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (ACTIVE_RENDERER == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(ACTIVE_RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
                //Set render scale
                SDL_RenderSetScale(ACTIVE_RENDERER, SCALE_X, SCALE_Y);
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

void close()
{
    //Destroy window
    SDL_DestroyRenderer(ACTIVE_RENDERER);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    ACTIVE_RENDERER = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main()
{
    /*if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
    }*/
    gameLoop();
    close();
    return 0;
}