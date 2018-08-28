#include "gameLogic.h"
#include "System/Physics/physicsEngine.h"
#include "System\graphics\graphicsEngine.h"
#include "scene\scene.h"
#include "math/lTimer.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "System\IO\inputManager.h"
#include "scene\debug_scenes\debug_scene0.h"
#include <iostream>

//The current scene in game
Scene *currentScene;

//Draws the background
void drawBackground();

//Main window for the game
LWindow *gameWindow;

//Current frame of the game
long currentFrame;

Room * getRoom()
{
    //return CURRENT_ROOM;
    return currentScene->getRoom();
}


void updateGameLogic()
{
    drawBackground();
    GameObject::updateAll();
}

void drawBackground()
{
    if (currentScene != NULL) {
        currentScene->getRoom()->renderBackground(Renderer::getCameraPosition());
    }
}


void closeGameLogic() {
    closeScene();
    delete(gameWindow);
    gameWindow = NULL;
}

void setScene()
{
    currentScene = new Debug_scene0();
    currentScene->setUpScene();
    GameObject::startAll();
}

void closeScene()
{
    delete(currentScene);
    currentScene = NULL;
}

void gameLoop() {

    gameWindow = GraphicsEngine::createGameWindow();

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
    while (!gameWindow->hasExited()) {
        capTimer.start();
        //Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000) avgFPS = 0;

        //Set text to be rendered
        timeText.str("");
        timeText << "Average Frames Per Second (With Cap)" << avgFPS;

        GraphicsEngine::clearWindow();
        updatePhysics();
        updateGameLogic();
        GraphicsEngine::renderGraphics();
        updateInputManager();
        //drawQuadTree(); //This will not work until this is put in GraphicsEngine

        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < GraphicsEngine::SCREEN_TICK_PER_FRAME) {
            //Wait remaining time
            SDL_Delay(GraphicsEngine::SCREEN_TICK_PER_FRAME - frameTicks);
        }
        else {
            float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            std::cout << "FPS LOW: " << avgFPS << ". Expected: " << GraphicsEngine::SCREEN_FPS << std::endl;
        }
        countedFrames++;
        currentFrame++;

        LWindow::updateAll();
    }
    closeGameLogic();
}