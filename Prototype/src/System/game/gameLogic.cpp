#include "gameLogic.h"
#include "System/Physics/physicsEngine.h"
#include "scene\scene.h"
#include "math/lTimer.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "System\IO\inputManager.h"
#include "scene\debug_scenes\debug_scene0.h"

list<GameObject*> ALL_GAMEOBJECTS = list<GameObject*>();
list<GameObject*> JUST_ACTIVATED_GAMEOBJECTS = list<GameObject*>();

//The room the player is currently in
Room *CURRENT_ROOM;

//The current scene in game
Scene *CURRENT_SCENE;

//Draws the background
void drawBackground();

//Calls start foreach gameObject that turned active this frame
void startGameObjects();

//Calls update foreach gameObject in gameObjects
void updateGameObjects();

//Updates all active hitboxes
void  updateHitBoxes();

void setRoom(Room *room)
{
    if (CURRENT_ROOM != NULL) {
        CURRENT_ROOM->unload();
    }
    CURRENT_ROOM = room;
    room->readFromFile();

    //Sets the bounds of the collider quadTree to room dimensions
    setQuadBounds(room->getDimensions());
}

Room * getRoom()
{
    return CURRENT_ROOM;
}


void updateGameLogic()
{
    drawBackground();
    startGameObjects();
    updateGameObjects();
}

void drawBackground()
{
    if (CURRENT_ROOM != NULL) {
        CURRENT_ROOM->background->render(0, 0);
    }
}

void startGameObjects()
{
    for each (GameObject *obj in JUST_ACTIVATED_GAMEOBJECTS)
    {
        obj->start();
    }

    //Empty list after all objects has called start method
    JUST_ACTIVATED_GAMEOBJECTS.empty();
}

void updateGameObjects() {
    for each (GameObject *obj in ALL_GAMEOBJECTS)
    {
        obj->update();
    }
}

//I think this is moved to the physics engine. Probably want to delete this method
void updateHitBoxes()
{
}

void closeGameLogic() {
    CURRENT_ROOM->unload();
}

void setScene()
{
    CURRENT_SCENE = &Debug_scene0();
}

void closeScene()
{
    ALL_GAMEOBJECTS.clear();
    JUST_ACTIVATED_GAMEOBJECTS.clear();
    delete(CURRENT_SCENE);
}

void gameLoop() {
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
    while (!quit) {
        pollExit(e, quit); //check if user exits window
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
        SDL_SetRenderDrawColor(MAIN_GAME_RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(MAIN_GAME_RENDERER);

        updatePhysics();

        updateGameLogic();

        //Update screen
        SDL_RenderPresent(MAIN_GAME_RENDERER);

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

    closeScene();
}