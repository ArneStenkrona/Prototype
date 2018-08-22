#pragma once
#include "System\Physics\collision.h"

class GameObject;
//Abstract class for components.
class Component {
public:

    //Initalize parent gameobject
    Component(GameObject *_object);

    //To be called on initialization in game.
    virtual void start();
    //To be called on each frame;
    virtual void update();

    //Updates all references to components
    virtual void updateComponents();

    //THESE COLLISION-METHODS SHOULD ONLY BE ACCESSIBLE BY GAMEOBJECT CLASS
    //THIS NEEDS TO BE FIXED
    //Called if entering collision with other entity
    virtual void onCollisionEnter(Collision *collision);
    //Called if currently colliding with other entity
    virtual void onColliding(Collision *collision);
    //Called if exiting collision with other entity
    virtual void onCollisionExit();

    //gameObject getter
    GameObject* getGameObject();

protected:
    //The Gameobject this is attached to
    GameObject *object;

    //Call this in constructor if a component is required by another
    //Returns the component
    template<class T>
    T *requireComponent();
};

template<class T>
T * Component::requireComponent()
{
    if (!is_base_of<Component, T>::value) {
        throw invalid_argument("Expected Component Type");
    }
    return object->hasComponent<T>() ? object->getComponent<T>() : object->addComponent<T>();
}