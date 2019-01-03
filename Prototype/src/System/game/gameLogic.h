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
#include "World/room.h"
#include "SDL_image.h"
#include "System/GUI/Window/lwindow.h"

class Scene;
class GameLogic {
public:
    //Gets the current room in game
    static Room *getRoom();
    //Makes sure that the room is set after the current iteration of the gameloop
    static void queueRoom(Room* room, int destX, int destY, GameObject* _enterer);

    //Sets the current scene in the game
    static void setScene();
    //Closes the current scene by removing all gameObjects
    static void closeScene();

    static void gameLoop();

    static void updateGameLoop();

    static void closeGameLogic();

    inline static bool getRoomChange() { return roomChange; }
private:
    //Current frame of the game
    static long currentFrame;
    //Main window for the game
    static LWindow *gameWindow;
    //The current scene in game
    static Scene *currentScene;
    //Room to be set. Null if no room is queued
    static Room* queuedRoom;
    //Destination coordinates in the queued room
    static Point destinationCoordinates;
    //Object entering queued room
    static GameObject * enterer;
    //True during the first frame of a new room
    static bool roomChange;

    //Sets the current room in game
    static void setRoom();
    //Draw the background for the room
    static void drawBackground();
};