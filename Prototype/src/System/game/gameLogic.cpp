#include "gameLogic.h"
#include "System/Physics/physicsEngine.h"


list<GameObject*> ALL_GAMEOBJECTS = list<GameObject*>();
list<GameObject*> JUST_ACTIVATED_GAMEOBJECTS = list<GameObject*>();

//The room the player is currently in
Room *CURRENT_ROOM;

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