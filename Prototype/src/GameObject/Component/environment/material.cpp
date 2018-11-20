#include "material.h"

Material::Material(GameObject * _object)
    : Component(_object)
{
}

void Material::rayHit(RayCastHit* hit)
{
    if (soundMap.find(hit->getMessage()) != soundMap.end())
        SoundManager::getSound(soundMap[hit->getMessage()])->play();
}

void Material::onCollisionEnter(Collision *collision)
{
    if (soundMap.find(collision->getOtherName()) != soundMap.end())
        SoundManager::getSound(soundMap[collision->getOtherName()])->play();
}
