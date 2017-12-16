/*
GameLogic is responsible for everything inside the game.
It initializes a window to be used.
It keeps track of gameObjects
It updates the gameObjects and runs the physics engine
The list of responsibilites is a bit convoluted as of now, I will work to correct this
*/

#pragma once
#include "GameObject/gameObject.h"
#include <list>
#include "../graphics/global_graphical_variables.h"
#include "World/room.h"
#include "SDL_image.h"
#include "System/GUI/Window/lwindow.h"

//Gets the render of the window
SDL_Renderer *getRenderer();

//Gets the current room in game
Room *getRoom();

//Sets the current scene in the game
void setScene();
//Closes the current scene by removing all gameObjects
void closeScene();

void gameLoop();

void updateGameLogic();

void closeGameLogic();
