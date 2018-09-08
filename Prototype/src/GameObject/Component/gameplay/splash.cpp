#include "Gameobject/gameObject.h"
#include "splash.h"

Splash::Splash(GameObject * _object) : Component(_object)
{
    position = requireComponent<Position>();
    velocity = requireComponent<Velocity>();
    rotation = requireComponent<Rotation>();
    sprite = requireComponent<Sprite>();
    animator = requireComponent<Animator>();
    renderer = requireComponent<SpriteRenderer>();

    animator->addClip({ "flash", 224, 225, 3 });
    animator->addClip({ "none", 255, 255, 0 });
}

void Splash::start()
{
    animator->playClip("none", true);
}

void Splash::update()
{
    animator->playClip("none", true);
}

void Splash::updateComponents()
{
}

void Splash::spawn(Point pos, double rot, Point pivot)
{
    position->position = pos;
    rotation->rotation = rot;
    rotation->pivot = pivot;
    animator->playClip("flash", false);
}
