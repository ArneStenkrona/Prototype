#pragma once
#include "System\Physics\collision.h"
#include "System\Physics\rayCastHit.h"

class GameObject;
//Abstract class for components.
class Component {
public:

    //Initalize parent gameobject
    Component(GameObject *_object);

    //To be called on initialization in game.
    virtual void start();
    //To be called on activation of object.
    virtual void onActivate();
    //To be called on inactivation of object
    virtual void onDeactivate();
    //To be called on each frame;
    virtual void update();
    //To be called on each frame after update()
    virtual void lateUpdate();

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

    //Called on rayHit
    virtual void rayHit(RayCastHit* hit);

    //gameObject getter
    inline GameObject* getGameObject() const { return object; }

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
    if (!std::is_base_of<Component, T>::value) {
        throw std::invalid_argument("Expected Component Type");
    }
    return object->hasComponent<T>() ? object->getComponent<T>() : object->addComponent<T>();
}