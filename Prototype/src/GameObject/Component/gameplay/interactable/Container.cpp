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
    sprite->setWidthHeight(2, 2);

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

void Container::update()
{
}

void Container::rayHit(RayCastHit * hit)
{
    if (hit->getMessage() == "lsr") {
        int indx = sprite->getTileIndex();
        if (indx < 4) {
            sprite->setTileIndex(indx + 1);
            if (indx + 1 == 4) {
                collider->setPolygon(Rectangular(Point(8, 25), 16, 7));
                SoundManager::getSound(SoundManager::GlASS_SHATTER_SOUND)->play();
            }
            else {
                SoundManager::getSound(SoundManager::GlASS_CRACKING_SOUND)->play();
            }
        }
        else {
            SoundManager::getSound(SoundManager::THUD_SOUND)->play();
        }
    }
}
