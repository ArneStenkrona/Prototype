#include "scene.h"

void Scene::setUpScene() {
}

void Scene::setRoom(Room *room)
{
    if (CURRENT_ROOM != NULL) {
        CURRENT_ROOM->unload();
    }
    CURRENT_ROOM = room;
    room->readFromFile();

    //Sets the bounds of the collider quadTree to room dimensions
    setQuadBounds(room->getDimensions());
}

Room * Scene::getRoom()
{
    return CURRENT_ROOM;
}