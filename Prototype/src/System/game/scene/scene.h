#pragma once
/*
A scene is loaded directly into the game.
A scene is one step above the hierarchy over room,
meaning that a scene contains rooms and is responsible
for swapping them.
*/

#include "GameObject/gameObject.h"
#include "World/room.h"
#include "System/Physics/physicsEngine.h"

class Scene {
public:
    Scene();
    ~Scene();

    //initialize scene
    virtual void setUpScene();

    //Gets the current room in scene
    inline Room *getRoom() const { return currentRoom; }
    //Sets the current room in scene
    void setRoom(Room *room);

protected:
    //The room the player is currently in
    Room *currentRoom;
};
