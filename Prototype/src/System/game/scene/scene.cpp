#include "scene.h"
#include "System\Physics\physicsEngine.h"

Scene::Scene() : currentRoom(NULL)
{
}

Scene::~Scene()
{
    delete(currentRoom);
    currentRoom = NULL;
}

void Scene::setUpScene() {
    //Test room
    Room *myRoom = new Room("Assets/Rooms/TEST.room");
    setRoom(myRoom);
}

void Scene::setRoom(Room *room)
{
    if (currentRoom != NULL) {
        currentRoom->unload();
    }
    currentRoom = room;
    currentRoom->load();
    currentRoom->instantiate();
    currentRoom->playMusic();

    //Sets the bounds of the collider quadTree to room dimensions
    PhysicsEngine::setQuadBounds(currentRoom->getDimensions());
}