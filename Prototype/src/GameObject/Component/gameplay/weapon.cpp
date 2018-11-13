#include "weapon.h"
#include "System\graphics\textureManager.h"
#include "System\IO\inputManager.h"
#include "GameObject\Prefabrications\prefabrications.h"
#include "System\Physics\physicsEngine.h"
#include "GameObject\objectPool.h"
#include "System\sound\soundManager.h"

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
    //sprite->setWidthHeight(2, 2); //uncomment if tile-size is set to 16x16
    animator->addClip(AnimationClip{ "idle", 240, 243, 7 });
    animator->addClip(AnimationClip{ "shoot", 244, 246, 7, {{244, SoundManager::LASER}} });
}

void Weapon::start()
{
    state = idle;
    rotation->pivot = Point(16,16);
}

void Weapon::update()
{
}

void Weapon::lateUpdate()
{
    //Update position and rotation
    int x, y;
    getMouseWorldCoordinates(x, y);
    Point direction = (renderer->getCameraPosition() + Point(x, y) - (ownerPosition->position + Point(16, 12))).normalized();
    if (direction.x < 0) {
        sprite->setMirror(false, true);
    }
    else {
        sprite->setMirror(false, false);
    }
    rotation->rotation = direction.toAngle();

    if (ownerPosition)
        position->position = ownerPosition->position + (10 * direction) - Point(0, 2);

    switch (state) {
    case idle:
        animator->playClip("idle", true);
        if (getKeyDown(MOUSE_LEFT)) {
            state = shoot;
        }
        break;
    case shoot:
        Point origin = position->position + (13 * direction) + Point(19, 16);
        Point end = position->position + (700 * direction) + Point(19, 16);
        RayCastHit* hit;
        if (raycast(origin, end, hit, 0, "lsr")) {
            end = hit->getIntersection();
            Point n = hit->getNormal();
            ObjectPool::instantiate("shrapnel", { end.x, end.y - 16, n.toAngle(), 0, 16 });
            delete(hit);
            hit = nullptr;
        }
        animator->playClip("shoot", false, true);
        Point splashPos = position->position + (10 * direction);
        ObjectPool::instantiate("flash", { splashPos.x, splashPos.y, rotation->rotation, rotation->pivot.x, rotation->pivot.y });
        ObjectPool::instantiate("beam", { origin.x, origin.y, end.x, end.y });
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
    int ownerLayer = owner->getComponent<Renderer>()->getRenderLayer();
    renderer->setRenderLayer((ownerLayer > 0 ? ownerLayer - 1 : ownerLayer                                     ));
}
