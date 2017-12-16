#pragma once
#include "GameObject/gameObject.h"
#include <list>
#include "../graphics/global_graphical_variables.h"
#include "World/room.h"

//List of all gameObjects
extern list<GameObject*> ALL_GAMEOBJECTS;
//List of all gameObjects that turned active this frame
extern list<GameObject*> JUST_ACTIVATED_GAMEOBJECTS;

//Sets the current room in game
void setRoom(Room *room);
//Gets the current room in game
Room *getRoom();

//Sets the current scene in the game
void setScene();
//Closes the current scene by removing all gameObjects
void closeScene();

void gameLoop();

void updateGameLogic();

void closeGameLogic();
