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
    virtual void onCollisionExit(Collision *collision);

    //gameObject getter
    GameObject* getGameObject();

protected:
    //The Gameobject this is attached to
    GameObject *object;

};

