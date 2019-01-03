#include "Door.h"
#include "GameObject\gameObject.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "System\game\gameLogic.h"

Door::Door(GameObject * _object)
    :Component(_object), destX(INT_MIN), destY(INT_MIN)
{
    collider = requireComponent<PolygonCollider>();
    collider->setStatic(true);
    collider->setTrigger(true);
    collider->setPolygon(Polyshape(32, 32, Point(0, 0)));
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
    if (!GameLogic::getRoomChange()) {
        GameLogic::queueRoom(new Room(roomFilePath), destX, destY, collision->getOtherCollider()->getGameObject());
    }
}
