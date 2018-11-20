#include "scene.h"
#include "System\Physics\physicsEngine.h"

Scene::Scene() : CURRENT_ROOM(NULL)
{
}

Scene::~Scene()
{
    delete(CURRENT_ROOM);
    CURRENT_ROOM = NULL;
}

void Scene::setUpScene() {
    //Test room
    Room *myRoom = new Room("Assets/Rooms/TEST.room");
    setRoom(myRoom);
    myRoom->instantiate();
    //myRoom->saveToFile();
}

void Scene::setRoom(Room *room)
{
    if (CURRENT_ROOM != NULL) {
        CURRENT_ROOM->unload();
    }
    CURRENT_ROOM = room;
    room->load();

    //Sets the bounds of the collider quadTree to room dimensions
    setQuadBounds(room->getDimensions());
}