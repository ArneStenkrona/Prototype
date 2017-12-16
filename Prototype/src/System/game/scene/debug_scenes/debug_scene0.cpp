#include "debug_scene0.h"
#include <iostream>

Debug_scene0::Debug_scene0() : Scene()
{
}

Debug_scene0::~Debug_scene0()
{
}

void Debug_scene0::setUpScene()
{
    GameObject *character = new GameObject();

    character->addComponent<Renderer>();
    character->addComponent<Movement>();

    character->addComponent<PolygonCollider>()->setStatic(false);
    character->getComponent<Position>()->position = Point(50, 50);

    GameObject *camera = new GameObject();
    camera->addComponent<Camera>()->setTarget(character);
    Renderer::setCamera(camera);

    //Test room
    Room *myRoom = new Room("Assets/Rooms/room1.txt");
    setRoom(myRoom);
    myRoom->saveToFile();
}

