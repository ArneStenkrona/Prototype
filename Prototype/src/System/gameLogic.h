#pragma once
#include "../GameObject/gameObject.h"
#include <list>
#include "graphics/global_graphical_variables.h"

//List of all gameObjects
extern list<GameObject*> ALL_GAMEOBJECTS;
//List of all gameObjects that turned active this frame
extern list<GameObject*> JUST_ACTIVATED_GAMEOBJECTS;

void updateGameLogic();

void closeGameLogic();
