#include "component.h"
#include "../gameObject.h"
Component::Component(GameObject *_object)
{
    object = _object;
}

Component::~Component()
{
}

void Component::start()
{
}

void Component::onActivate()
{
}

void Component::onDeactivate()
{
}

void Component::update()
{
}

void Component::lateUpdate()
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

