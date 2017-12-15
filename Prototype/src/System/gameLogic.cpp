#include "gameLogic.h"
//#include "physicsEngine.h"


list<GameObject*> ALL_GAMEOBJECTS = list<GameObject*>();
list<GameObject*> JUST_ACTIVATED_GAMEOBJECTS = list<GameObject*>();

//Calls start foreach gameObject that turned active this frame
void startGameObjects();

//Calls update foreach gameObject in gameObjects
void updateGameObjects();


void updateGameLogic()
{
    startGameObjects();
    updateGameObjects();
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
