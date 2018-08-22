#include "velocity.h"
#include "GameObject/gameObject.h"
#include <iostream>

Velocity::Velocity(GameObject * _object) : velocity(Point(0, 0)), Component(_object)
{
    position = requireComponent<Position>();

}

void Velocity::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
}

void Velocity::start()
{
}

void Velocity::update()
{
    position->position += velocity;
}
