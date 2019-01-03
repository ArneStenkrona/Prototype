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
    void setDestination(Point _destination) { destination = _destination; }
    void setPolygon(Polyshape p);


private:
    //Filepath to the room the door leads to;
    std::string roomFilePath;
    //Destination coordinates
    Point destination;

    PolygonCollider* collider;
    void onCollisionEnter(Collision *collision);

};