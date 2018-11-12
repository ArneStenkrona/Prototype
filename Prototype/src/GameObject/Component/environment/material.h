#pragma once
#include "GameObject\Component\component.h"
#include "System\sound\soundManager.h"
#include <map>

class GameObject;
class Material : public Component {
public:

    Material(GameObject *_object);
    
    void rayHit(RayCastHit* hit);
    void onCollisionEnter(Collision *collision);
    //Mapping rayhit messages to sound
    std::map<std::string, SoundManager::SOUNDS> soundMap;

private:
};