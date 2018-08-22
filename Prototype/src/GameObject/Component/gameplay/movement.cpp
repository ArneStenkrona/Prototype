#include "movement.h"
#include "GameObject/gameObject.h"
#include <iostream>
#include "SDL.h"
#include "System/IO/inputManager.h"
#include <algorithm>

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
    //printf("ENTER\n");
}

void Movement::onColliding(Collision *collision)
{
    if (velocity->velocity.dot(collision->collisionNormal) < 0.000001) {
        if (collision->collisionTime < 0.0) {
            position->position -= collision->collisionNormal * collision->collisionTime - 0.001 * velocity->velocity;
            Point perpNormal = Point(-collision->collisionNormal.y, collision->collisionNormal.x);
            velocity->velocity = velocity->velocity.dot(perpNormal) * perpNormal;

        }
        else {
            velocity->velocity = collision->correctedVelocity();
        }
    }
    if (collision->collisionNormal.dot(Point::up) < 0.000001)
        grounded = true;

    //printf("COLLIDING\n");
}

void Movement::onCollisionExit()
{
    //printf("EXIT\n");
}


void Movement::start()
{
}

void Movement::update()
{


    //Initalize direction vector to 0,0
    Point direction = Point();

    if (abs(velocity->velocity.x) < 1)
        state = idle;

    if (getKey(INPUT_KEY_A))
    {
        direction += Point::left;
        if (velocity->velocity.x < -0.01) state = running;
    }
    if (getKey(INPUT_KEY_D))
    {
        direction += Point::right;
        if (velocity->velocity.x > 0.01) state = running;
    }

    if (getKey(INPUT_KEY_W))
    {
        direction += Point::down;
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
            sprite->setMirror(true);
        if (getKey(INPUT_KEY_D))
            sprite->setMirror(false);
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
        velocity->velocity += Point::up * 0.6;
    }

    if (getKeyDown(INPUT_KEY_SPACE)) {
        if (velocity->velocity.y > -1) {
            velocity->velocity -= Point::up * 10;
        }
    }
    if(velocity->velocity.y > 3.0)
        grounded = false;
}
