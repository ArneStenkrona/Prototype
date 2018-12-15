#pragma once
#include "../../component.h"
#include "math\polygon.h"
class GameObject;
class Door : public Component {
public:
    Door(GameObject *_object);

    void updateComponents();

    //Sets filepath to the room the door leads to
    void setPath(std::string path) { roomFilePath = path; }
    void setPolygon(Polyshape p);


private:
    //Filepath to the room the door leads to;
    std::string roomFilePath;

    PolygonCollider* collider;
    void onCollisionEnter(Collision *collision);

    //The door number identifies this door within the room
    //Value of -1 indicates a non-functioning door
    int doorNumber;
};