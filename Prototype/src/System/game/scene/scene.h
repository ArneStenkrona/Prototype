#pragma once
/*
A scene is loaded directly into the game.
A scene is one step above the hierarchy over room,
meaning that a scene contains rooms and is responsible
for swapping theme.
*/

#include "GameObject/gameObject.h"
#include "GameObject/Component/graphics/camera.h"
#include "GameObject/Component/graphics/renderer.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject/Component/gameplay/movement.h"
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "World/room.h"
#include "System/Physics/physicsEngine.h"

class Scene {
public:
    Scene();
    ~Scene();

    //initialize scene
    virtual void setUpScene();

    //Gets the current room in scene
    Room *getRoom();

protected:
    //The room the player is currently in
    Room *CURRENT_ROOM;
    //Sets the current room in scene
    void setRoom(Room *room);

};
