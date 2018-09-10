#include "component.h"
#include "../gameObject.h"
Component::Component(GameObject *_object)
{
    object = _object;
}

void Component::start()
{
}

void Component::awake()
{
}

void Component::update()
{
}

void Component::updateComponents()
{
}

void Component::onCollisionEnter(Collision *collision)
{
}

void Component::onColliding(Collision *collision)
{
}

void Component::onCollisionExit()
{
}

void Component::rayHit(RayCastHit * hit)
{
}

GameObject * Component::getGameObject()
{
    return object;
}
