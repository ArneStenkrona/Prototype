#include "gameObject.h"
#include "../System/gameLogic.h"

//getComponent() is in header file, due to being a template function
//setComponent() is in header file, due to being a template function

GameObject::GameObject() : components(list<Component*>()), active(true)
{
    ALL_GAMEOBJECTS.push_back(this);
}

GameObject::~GameObject()
{
    for each (Component *comp in components)
    {
        delete comp;
        comp = nullptr;
    }

    components.clear();

    ALL_GAMEOBJECTS.remove(this);
}

bool GameObject::getActive()
{
    return active;
}

void GameObject::setActive(bool b)
{
    active = b;
    //This will be sent to gameLogics list of objects activated this frame, which will call this objects start method;
    JUST_ACTIVATED_GAMEOBJECTS.push_back(this);
}

void GameObject::updateComponents()
{
    for each  (Component *t in components)
    {
        t->updateComponents();
    }
}

void GameObject::start()
{
    for each (Component *comp in components)
    {
        comp->start();
    }
}

void GameObject::update()
{
    for each (Component *comp in components)
    {
        comp->update();
    }
}