#pragma once

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

protected:
    //The Gameobject this is attached to
    GameObject *object;


};
