#include "Container.h"
#include "System\graphics\textureManager.h"
#include "GameObject\gameObject.h"

Container::Container(GameObject * _object) : Component(_object)
{
    position = requireComponent<Position>();
    rotation = requireComponent<Rotation>();
    sprite = requireComponent<Sprite>();
    renderer = requireComponent<SpriteRenderer>();
    collider = requireComponent<PolygonCollider>();

    sprite->texture = &TextureManager::spriteSheets[TextureManager::OBJECTS_1];

    collider->setStatic(true);
    collider->setPolygon(Rectangular(Point(8, 8), 16, 24));
}

void Container::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
    collider = (object->hasComponent<PolygonCollider>()) ? object->getComponent<PolygonCollider>() : collider;
}

void Container::rayHit(RayCastHit * hit)
{
    int indx = sprite->getTileIndex();
    if (indx < 4) {
        sprite->setTileIndex(indx + 1);
        if (indx + 1 == 4) {
            collider->setPolygon(Rectangular(Point(8, 25), 16, 7));
        }
    }
}
