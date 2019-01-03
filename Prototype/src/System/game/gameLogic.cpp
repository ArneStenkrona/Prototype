#include "gameLogic.h"
#include "System/Physics/physicsEngine.h"
#include "System\graphics\graphicsEngine.h"
#include "System\sound\soundManager.h"
#include "scene\scene.h"
#include "math/lTimer.h"
#include "System\IO\inputManager.h"
#include "scene\debug_scenes\debug_scene0.h"
#include "GameObject\objectPool.h"
#include "tools\timeMacros.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

long GameLogic::currentFrame = 0;
bool GameLogic::roomChange = false;
LWindow* GameLogic::gameWindow = nullptr;
Scene* GameLogic::currentScene = nullptr;
Room* GameLogic::queuedRoom = nullptr;

Room * GameLogic::getRoom()
{
    //return CURRENT_ROOM;
    return currentScene->getRoom();
}

void GameLogic::queueRoom(Room * room)
{
    queuedRoom = room;
}

void GameLogic::setRoom()
{
    currentScene->setRoom(queuedRoom);
    PhysicsEngine::resetPhysics();
    queuedRoom = nullptr;
    GameObject::startAll();
    roomChange = true;
}


void GameLogic::updateGameLoop()
{
    GraphicsEngine::clearWindow();
    drawBackground();
    GameObject::updateAll();
    PhysicsEngine::updatePhysics();
    GameObject::lateUpdateAll();
    GraphicsEngine::renderGraphics();
    updateInputManager();
}

void GameLogic::drawBackground()
{
    if (currentScene != NULL) {
        currentScene->getRoom()->renderBackground(Renderer::getCameraPosition());
    }
}


void GameLogic::closeGameLogic() {
    closeScene();
    delete(gameWindow);
    gameWindow = NULL;
}

void GameLogic::setScene()
{
    currentScene = new Debug_scene0();
    currentScene->setUpScene();
    GameObject::startAll();
}

void GameLogic::closeScene()
{
    delete(currentScene);
    currentScene = NULL;
}



void GameLogic::gameLoop() {

    gameWindow = GraphicsEngine::createGameWindow();

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    //Start counting frames per second
    fpsTimer.start();

    //Initalize input Manager
    initializeInputManager();
    //Initalize texture manager
    TextureManager::initalizeTextureManager();
    SoundManager::initalizeSoundManager();

    setScene();


    //While games is running
    while (!gameWindow->hasExited()) {
        if (queuedRoom)
            setRoom();
        capTimer.start();
        updateGameLoop();
        roomChange = false;

        //If frame finished early
        int frameTicks = capTimer.getMicroSeconds();
        if (frameTicks < GraphicsEngine::MICROSECONDS_PER_FRAME) {
            //Wait remaining time
            SDL_Delay((GraphicsEngine::MICROSECONDS_PER_FRAME - frameTicks) / 1000);
        }
        else {
            if (frameTicks > GraphicsEngine::MICROSECONDS_PER_FRAME + 1) {
                float fps = 1000000 / frameTicks;
                std::cout << "FPS LOW: " << fps << ". Expected: " << GraphicsEngine::SCREEN_FPS << std::endl;
            }
        }
        currentFrame++;

        LWindow::updateAll();
    }
    closeGameLogic();
}