#include "component.h"
#include "../gameObject.h"
Component::Component(GameObject *_object)
{
    object = _object;
}

void Component::start()
{
}

void Component::update()
{
}

void Component::updateComponents()
{
}
