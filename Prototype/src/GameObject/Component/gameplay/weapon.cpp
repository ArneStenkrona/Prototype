#include "weapon.h"
#include "System\graphics\textureManager.h"
#include "System\IO\inputManager.h"
#include "GameObject\prefabrications.h"

Weapon::Weapon(GameObject * _object) : Component(_object)
{
    position = requireComponent<Position>();
    velocity = requireComponent<Velocity>();
    rotation = requireComponent<Rotation>();
    sprite = requireComponent<Sprite>();
    animator = requireComponent<Animator>();
    renderer = requireComponent<SpriteRenderer>();

    sprite->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    sprite->setTileIndex(240);
    animator->addClip(AnimationClip{ "idle", 240, 243, 7 });
    animator->addClip(AnimationClip{ "shoot", 244, 246, 7 });

    splash = muzzleFlash()->getComponent<Splash>();
    beam = laserBeam()->getComponent<Beam>();
}

void Weapon::start()
{
    state = idle;
    rotation->pivot = Point(16,16);
    beam->setPoints(Point(0,0), Point(64,64));
}

void Weapon::update()
{
    //Update position and rotation
    int x, y;
    getMouseCoordinates(&x, &y);
    Point direction = (renderer->getCameraPosition() + (Point(x, y) * 0.5) - (ownerPosition->position + Point(16, 12))).normalized();
    if (direction.x < 0) {
        sprite->setMirror(false, true);
    }
    else {
        sprite->setMirror(false, false);
    }
    rotation->rotation = direction.toAngle();

    if (ownerPosition)
        position->position = ownerPosition->position + (13 * direction) - Point(0, 2);

    switch (state) {
    case idle:
        animator->playClip("idle", true);
        if (getMouseClick()) {
            state = shoot;
        }    
        break;
    case shoot:
        animator->playClip("shoot", false, true);
        splash->spawn(position->position + (10 *  direction), rotation->rotation, rotation->pivot);
        beam->setPoints(position->position + (13 *  direction) + Point(19,16), position->position + (1000 * direction) + Point(19, 16));
        ownerVelocity->velocity -= direction * 5;
        state = idle;
        break;
    }
    prevState = state;
}

void Weapon::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    velocity = (object->hasComponent<Velocity>()) ? object->getComponent<Velocity>() : velocity;
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
    animator = (object->hasComponent<Animator>()) ? object->getComponent<Animator>() : animator;
}

void Weapon::setOwner(GameObject* owner)
{
    ownerPosition = owner->getComponent<Position>();
    ownerVelocity = owner->getComponent<Velocity>();
}
