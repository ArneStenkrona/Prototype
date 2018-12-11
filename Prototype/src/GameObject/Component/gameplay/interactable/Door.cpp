#include "Door.h"
#include "GameObject\gameObject.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "System\game\gameLogic.h"

Door::Door(GameObject * _object)
    :Component(_object)
{
    collider = requireComponent<PolygonCollider>();
    collider->setStatic(true);
    collider->setPolygon(Rectangular(Point(0, 0), 32, 32));
}

void Door::updateComponents()
{
    collider = (object->hasComponent<PolygonCollider>()) ? object->getComponent<PolygonCollider>() : collider;
}


void Door::setPolygon(Polyshape p)
{
    collider->setPolygon(p);
}

void Door::onCollisionEnter(Collision * collision)
{
    GameLogic::queueRoom(new Room(roomFilePath));
}
