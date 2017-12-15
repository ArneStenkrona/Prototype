#include "velocity.h"
#include "GameObject/gameObject.h"
#include <iostream>

Velocity::Velocity(GameObject * _object) : velocity(Point(0, 0)), Component(_object)
{
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }
    else {
        position = object->addComponent<Position>();
    }
}

void Velocity::updateComponents()
{
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }

}

void Velocity::start()
{
}

void Velocity::update()
{
    position->position += velocity;
}
