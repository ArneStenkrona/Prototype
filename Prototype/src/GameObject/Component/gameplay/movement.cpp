#include "movement.h"
#include "GameObject/gameObject.h"
#include <iostream>
#include "SDL.h"
#include "System/IO/inputManager.h"

Movement::Movement(GameObject *_object) : Component(_object),
state(nullState), prevState(nullState), transitionCounter(0)
{
    //Check for velocity component
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }
    else {
        velocity = object->addComponent<Velocity>();
    }

    //Check for sprite component
    if (object->hasComponent<Sprite>()) {
        sprite = object->getComponent<Sprite>();
    }
}

void Movement::updateComponents()
{
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }

    if (object->hasComponent<Sprite>()) {
        sprite = object->getComponent<Sprite>();
    }
}


void Movement::start()
{
}

void Movement::update()
{


    //Initalize direction vector to 0,0
    Point direction = Point();

    state = idle;

    if (getKey(INPUT_KEY_A))
    {
        direction += Point::left;
        state = running;
    }
    if (getKey(INPUT_KEY_D))
    {
        direction += Point::right;
        state = running;
    }

    if (getKey(INPUT_KEY_W))
    {
        direction += Point::down;
    }
    if (getKey(INPUT_KEY_S))
    {
        direction += Point::up;
    }
    //DIRTY HACK! SHOULD BE FIXED BY CREATING A PROPER ANIMATION DATA STRUCTURE
    switch (state) {
    case idle :
        if (transitionCounter == 0) {
            sprite->setAnimationIndicies(16, 16);
            transitionCounter--;
        } else if (transitionCounter > 0)
            transitionCounter--;
        break;
    case running :
        if (prevState != running) 
            sprite->setAnimationIndicies(0, 4);
        if (getKeyDown(INPUT_KEY_A))
            sprite->setMirror(true);
        if (getKeyDown(INPUT_KEY_D))
            sprite->setMirror(false);
        transitionCounter = (4 - sprite->getTileIndex()) * 3;
        break;
    }
    prevState = state;

    direction = direction.normalized();

    Point deltaTerm = direction * acceleration;

    //Limit speed
    if ((velocity->velocity + deltaTerm).magnitude() < speed) {
        velocity->velocity += deltaTerm;
    }
    //Add drag
    velocity->velocity = Point(velocity->velocity.x * drag, velocity->velocity.y);// *drag);

    //Add gravity
    if (velocity->velocity.y < 10) {
        velocity->velocity += Point::up * 0.6;
    }

    if (getKeyDown(INPUT_KEY_SPACE)) {
        if (velocity->velocity.y > -1) {
            velocity->velocity -= Point::up * 10;
        }
    }


}
