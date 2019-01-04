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
LWindow* GameLogic::gameWindow = nullptr;
Scene* GameLogic::currentScene = nullptr;
Room* GameLogic::queuedRoom = nullptr;
bool GameLogic::roomChange = false;
Point GameLogic::destinationCoordinates = Point(0,0);
GameObject * GameLogic::enterer = nullptr;

Room * GameLogic::getRoom()
{
    //return CURRENT_ROOM;
    return currentScene->getRoom();
}

void GameLogic::queueRoom(Room * room, int destX, int destY, GameObject *_enterer)
{
    queuedRoom = room;
    destinationCoordinates = Point(destX, destY);
    enterer = _enterer;
}

void GameLogic::setRoom()
{
    currentScene->setRoom(queuedRoom);
    PhysicsEngine::resetPhysics();

    Position *p = enterer->getComponent<Position>();
    if (p) {
        Point pos = p->position;
        //If coordinates are less than some really small value, use existing coordinate
        if (destinationCoordinates.x > -256 * 256 * 256)
            pos.x = Tile::TILE_SIZE * destinationCoordinates.x;
        if (destinationCoordinates.y > -256 * 256 * 256)
            pos.y = Tile::TILE_SIZE * destinationCoordinates.y;
        p->position = pos;
    }

    queuedRoom = nullptr;
    destinationCoordinates = Point(0,0);
    enterer = nullptr;
    roomChange = true;
    GameObject::startAll();
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
                float fps = 1000000.f / frameTicks;
                std::cout << "FPS LOW: " << fps << ". Expected: " << GraphicsEngine::SCREEN_FPS << std::endl;
            }
        }
        currentFrame++;

        LWindow::updateAll();
    }
    closeGameLogic();
}