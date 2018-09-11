#include "Gameobject/gameObject.h"
#include "splash.h"
#include "GameObject\objectPool.h"

Splash::Splash(GameObject * _object) : Component(_object), clipName("flash")
{
    position = requireComponent<Position>();
    velocity = requireComponent<Velocity>();
    rotation = requireComponent<Rotation>();
    sprite = requireComponent<Sprite>();
    animator = requireComponent<Animator>();
    renderer = requireComponent<SpriteRenderer>();

    animator->addClip({ clipName, 224, 225, 3 });
    animator->addClip({ "none", 255, 255, 0 });
}

void Splash::start()
{
    animator->playClip("none", true);
}


void Splash::awake()
{
    std::vector<double> args = object->getArgs();
    if (args.size() >= 5) {
        position->position = Point(args[0], args[1]);
        rotation->rotation = args[2];
        rotation->pivot = Point(args[3], args[4]);
        animator->playClip(clipName, false);
        woke = true;
    } 
}

void Splash::update()
{
    if (woke && animator->getCurrentClip() == "none") {
        woke = false;
        ObjectPool::repool(object);
    } 
    animator->playClip("none", true);
}

void Splash::updateComponents()
{
}

void Splash::setClip(AnimationClip clip)
{
    animator->addClip(clip);
    clipName = clip.name;
}