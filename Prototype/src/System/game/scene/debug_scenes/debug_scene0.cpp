#include "debug_scene0.h"

void Debug_scene0::setUpScene()
{
    GameObject character = GameObject();

    character.addComponent<Renderer>();
    character.addComponent<Movement>();

    character.addComponent<PolygonCollider>()->setStatic(false);
    character.getComponent<Position>()->position = Point(50, 50);

    GameObject camera = GameObject();
    camera.addComponent<Camera>()->setTarget(&character);
    Renderer::setCamera(&camera);

    //Test room
    Room myRoom = Room("Assets/Rooms/room1.txt");
    setRoom(&myRoom);
    myRoom.saveToFile();
}

