#pragma once
#include <list>
#include "Component/component.h"

using namespace::std;

//Game objects by default are empty. Components can be added to them to create behaviour.
//Only one of each component can be held.
class GameObject {

public:

    //Constructor adds object to list of all gameObjects in gameLogic
    GameObject();

    //Destructor deletes all components
    ~GameObject();

    //Call start() in every component
    void start();
    //Call update() in every component
    void update();

    //Gets component of specified type. Returns null if no such component exists
    //Returns null if T is not a component
    template<class T>
    T *getComponent();

    //Creates a new component of specified type and inserts into components list.
    //If component of type already exists it is replaced and destroyed.
    //Returns the new component.
    //Returns null if T is not a component
    template<class T>
    T *addComponent();

    //Removes component of specified type, if it exists
    template<class T>
    void *removeComponent();

    //Returns true if specified type exists
    template<class T>
    bool hasComponent();


    //returns active
    bool getActive();
    //sets active
    void setActive(bool b);

private:

    //Updates all components references
    void updateComponents();

    //Components contained by this gameobject
    list<Component*> components;

    //If active, this gameObject will be updates each frame
    bool active;
};


//Here instead of .cpp file due to being a template function
template<class T>
T * GameObject::getComponent()
{

    for each  (Component *t in components)
    {
        if (dynamic_cast<T*>(t)) {
            return (T*)t;
        }
    }

    return NULL;
}

//Here instead of .cpp file due to being a template function
template<class T>
T * GameObject::addComponent()
{

    if (!std::is_base_of<Component, T>::value) {
        return NULL;
    }

    removeComponent<T>();

    T *component = new T(this);

    components.push_back(component);

    updateComponents();

    return component;
}

template<class T>
void * GameObject::removeComponent()
{

    if (!std::is_base_of<Component, T>::value) {
        return 0;
    }

    Component *comp = NULL;



    for each  (Component *t in components)
    {
        if (dynamic_cast<T*>(t)) {
            comp = t;
        }
    }

    if (comp) {
        components.remove(comp);
        delete comp;
        comp = NULL;
    }

    updateComponents();

    return 0;
}

template<class T>
bool GameObject::hasComponent()
{

    for each  (Component *t in components)
    {
        if (dynamic_cast<T*>(t)) {
            return true;
        }
    }
    return false;
}
