#include "movement.h"
#include "GameObject/gameObject.h"
#include <iostream>
#include "SDL.h"
#include "System/IO/inputManager.h"

Movement::Movement(GameObject *_object) : Component(_object)
{
    //Check for velocity component
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }
    else {
        velocity = object->addComponent<Velocity>();
    }
}

void Movement::updateComponents()
{
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }
}


void Movement::start()
{
}

void Movement::update()
{


    //Initalize direction vector to 0,0
    Point direction = Point();

    if (getKey(INPUT_KEY_A))
    {
        direction += Point::left;
    }
    if (getKey(INPUT_KEY_D))
    {
        direction += Point::right;
    }

    if (getKey(INPUT_KEY_W))
    {
        direction += Point::down;
    }
    if (getKey(INPUT_KEY_S))
    {
        direction += Point::up;
    }


    direction = direction.normalized();

    Point deltaTerm = direction * acceleration;

    //Limit speed
    if ((velocity->velocity + deltaTerm).magnitude() < speed) {
        velocity->velocity += deltaTerm;
    }
    //Add drag
    velocity->velocity = Point(velocity->velocity.x * drag, velocity->velocity.y * drag);

    //Add gravity
    if (velocity->velocity.y < 10) {
        //	velocity->velocity += Point::up * 0.2;
    }

    if (getKeyDown(INPUT_KEY_SPACE)) {
        if (velocity->velocity.y > -1) {
            velocity->velocity -= Point::up * 5;
        }
    }


}
