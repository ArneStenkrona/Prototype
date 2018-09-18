#include "movement.h"
#include "GameObject/gameObject.h"
#include <iostream>
#include "SDL.h"
#include "System/IO/inputManager.h"
#include <algorithm>
#include "System\Physics\physicsEngine.h"

Movement::Movement(GameObject *_object) : Component(_object),
state(nullState), prevState(nullState), transitionCounter(0),
grounded(false)
{
    position = requireComponent<Position>();
    velocity = requireComponent<Velocity>();
    sprite = requireComponent<Sprite>();
    animator = requireComponent<Animator>();
}

void Movement::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    velocity = (object->hasComponent<Velocity>()) ? object->getComponent<Velocity>() : velocity;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
    animator = (object->hasComponent<Animator>()) ? object->getComponent<Animator>() : animator;
}

void Movement::onCollisionEnter(Collision * collision)
{
}

void Movement::onColliding(Collision *collision)
{
}

void Movement::onCollisionExit()
{
}


void Movement::start()
{
}

void Movement::update()
{
    Point origin = position->position + Point(3, 39.7);
    grounded = raycast(origin, origin  + Point(26, 2), 0) || raycast(origin + Point(26, 0), origin + Point(-26, 2), 0);
    //Initalize direction vector to 0,0
    Point direction = Point();

    if (abs(velocity->velocity.x) < 1)
        state = idle;

    if (getKey(INPUT_KEY_A))
    {
        direction += Point::left;
        if (velocity->velocity.x < -2) state = running;
    }
    if (getKey(INPUT_KEY_D))
    {
        direction += Point::right;
        if (velocity->velocity.x > 2) state = running;
    }

    if (getKey(INPUT_KEY_W))
    {
        //direction += Point::down;
    }
    if (getKey(INPUT_KEY_S))
    {
        direction += Point::up;
    }
    if (!grounded) state = falling;

    //DIRTY HACK! SHOULD BE FIXED BY CREATING A PROPER ANIMATION DATA STRUCTURE
    switch (state) {
    case idle :
        animator->playClip("idle", prevState == running);
        animator->setSpeedFactor(1);
        break;
    case running :
        animator->setSpeedFactor(min(2.4, 5.8 / abs(velocity->velocity.x)));
        if (prevState != running) {
            animator->playClip("running", false);
        }
        if (getKey(INPUT_KEY_A))
            sprite->setMirror(true, false);
        if (getKey(INPUT_KEY_D))
            sprite->setMirror(false, false);
        break;
    case falling :
        animator->playClip("falling", false);
        animator->setSpeedFactor(1);
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
        velocity->velocity += Point::up * 0.4;
    }

    if (getKeyDown(INPUT_KEY_SPACE)) {
        if (velocity->velocity.y > -1) {
            velocity->velocity -= Point::up * 10;
        }
    }
}
