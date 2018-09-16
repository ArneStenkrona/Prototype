#include "gameObject.h"
#include "../System/game/gameLogic.h"
#include "Component\geometry\polygonCollider.h"
#include <iostream>

//getComponent() is in header file, due to being a template function
//setComponent() is in header file, due to being a template function

GameObject::GameObject(std::string _name) : components(list<Component*>()), active(true), name(_name)
{
    all_gameObjects.insert(this);
}

set<GameObject*> GameObject::all_gameObjects = set<GameObject*>();
set<GameObject*> GameObject::just_activated_gameObjects = set<GameObject*>();
set<GameObject*> GameObject::just_deactivated_gameObjects = set<GameObject*>();


GameObject::~GameObject()
{
    for each (Component *comp in components)
    {
        delete comp;
        comp = nullptr;
    }

    components.clear();

    all_gameObjects.erase(this);
}

void GameObject::startAll()
{
    for each (GameObject* obj in all_gameObjects)
    {
        if (obj->active) obj->onActivate();
    }
    for each (GameObject *obj in all_gameObjects)
    {
        obj->start();
    }
}

void GameObject::updateAll()
{

    for each (GameObject *obj in all_gameObjects)
    {
        if (obj->active) obj->update();
    }
    for each (GameObject *obj in all_gameObjects)
    {
        if (obj->active) obj->lateUpdate();
    }

    for each (GameObject* obj in just_activated_gameObjects)
    {
        if (obj->active) obj->onActivate();
    }
    //Empty list after all objects has called activate method
    just_activated_gameObjects.clear();

    for each (GameObject* obj in just_deactivated_gameObjects)
    {
        if (obj->active) obj->onDeactivate();
    }
    //Empty list after all objects has called activate method
    just_deactivated_gameObjects.clear();
}

void GameObject::setActive(bool b)
{
    //This will be sent to gameLogics list of objects activated this frame, which will call this objects start method;
    if (b && !active) {
        just_deactivated_gameObjects.erase(this);
        just_activated_gameObjects.insert(this);
    }
    else if (!b && active) {
        just_activated_gameObjects.erase(this);
        just_deactivated_gameObjects.insert(this);
    }
    active = b;
}

void GameObject::updateComponents()
{
    for each  (Component *t in components)
    {
        t->updateComponents();
    }
}

void GameObject::onCollisionEnter(Collision *collision)
{
    if (hasComponent<PolygonCollider>()) {
        for each (Component *comp in components)
        {
            comp->onCollisionEnter(collision);
        }
    }
}

void GameObject::onColliding(Collision *collision)
{
        for each (Component *comp in components)
        {
            comp->onColliding(collision);
        }
}

void GameObject::onCollisionExit()
{
        for each (Component *comp in components)
        {
            comp->onCollisionExit();
        }
}

void GameObject::rayHit(RayCastHit * hit)
{
        for each (Component *comp in components)
        {
            comp->rayHit(hit);
        }
}

void GameObject::setArgs(std::vector<double> _args)
{
    args = _args;
}

void GameObject::start()
{
    for each (Component *comp in components)
    {
        comp->start();
    }
}

void GameObject::onActivate()
{
    for each (Component *comp in components)
    {
        comp->onActivate();
    }
}

void GameObject::onDeactivate()
{
    for each (Component *comp in components)
    {
        comp->onDeactivate();
    }
}

void GameObject::update()
{
    for each (Component *comp in components)
    {
        comp->update();
    }
}

void GameObject::lateUpdate()
{
    for each (Component *comp in components)
    {
        comp->lateUpdate();
    }
}
