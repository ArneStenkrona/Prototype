#include "gameLogic.h"
#include "System/Physics/physicsEngine.h"
#include "scene\scene.h"
#include "math/lTimer.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "System\IO\inputManager.h"
#include "scene\debug_scenes\debug_scene0.h"

//The current scene in game
Scene *CURRENT_SCENE;

//Draws the background
void drawBackground();

//Main window for the game
LWindow *game_window;

SDL_Renderer * getRenderer()
{
    if (game_window != NULL) {
        return game_window->getRenderer();
    }
    else {
        return nullptr;
    }
}

Room * getRoom()
{
    //return CURRENT_ROOM;
    return CURRENT_SCENE->getRoom();
}


void updateGameLogic()
{
    drawBackground();
    GameObject::updateAll();
}

void drawBackground()
{
    if (CURRENT_SCENE != NULL) {
        CURRENT_SCENE->getRoom()->background->render(0, 0);
    }
}


void closeGameLogic() {
    closeScene();
    delete(game_window);
    game_window = NULL;
}

void setScene()
{
    CURRENT_SCENE = new Debug_scene0();
    CURRENT_SCENE->setUpScene();
}

void closeScene()
{
    CURRENT_SCENE = NULL;
}

void gameLoop() {

    game_window = new LWindow(SCREEN_WIDTH,SCREEN_HEIGHT,SCALE_X,SCALE_Y);
    ACTIVE_RENDERER = getRenderer();

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    //In memory text stream
    std::stringstream timeText;
    //Start counting frames per second
    long countedFrames = 0;
    fpsTimer.start();

    //Initalize input Manager
    initializeInputManager();
    //Initalize texture manager
    TextureManager::initalizeTextureManager();

    setScene();

    //While games is running
    while (!game_window->getExit()) {
        game_window->update();
        capTimer.start();
        //Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000)
        {
            avgFPS = 0;
        }
        //Set text to be rendered
        timeText.str("");
        timeText << "Average Frames Per Second (With Cap)" << avgFPS;

        //Clear screen
        SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(getRenderer());

        updatePhysics();

        updateGameLogic();

        //Update screen
        SDL_RenderPresent(getRenderer());

        updateInputManager();

        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICK_PER_FRAME) {
            //Wait remaining time
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
        }
        else {

        }
        countedFrames++;
    }

    closeGameLogic();
}