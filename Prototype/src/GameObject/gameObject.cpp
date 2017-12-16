#include "gameObject.h"
#include "../System/game/gameLogic.h"

//getComponent() is in header file, due to being a template function
//setComponent() is in header file, due to being a template function

GameObject::GameObject() : components(list<Component*>()), active(true)
{
    all_gameObjects.push_back(this);
}

list<GameObject*> GameObject::all_gameObjects = list<GameObject*>();
list<GameObject*> GameObject::just_activated_gameObjects = list<GameObject*>();

GameObject::~GameObject()
{
    for each (Component *comp in components)
    {
        delete comp;
        comp = nullptr;
    }

    components.clear();

    all_gameObjects.remove(this);
}

void GameObject::updateAll()
{
    for each (GameObject *obj in just_activated_gameObjects)
    {
        obj->start();
    }

    //Empty list after all objects has called start method
    just_activated_gameObjects.empty();

    for each (GameObject *obj in all_gameObjects)
    {
        obj->update();
    }
}

bool GameObject::getActive()
{
    return active;
}

void GameObject::setActive(bool b)
{
    active = b;
    //This will be sent to gameLogics list of objects activated this frame, which will call this objects start method;
    just_activated_gameObjects.push_back(this);
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