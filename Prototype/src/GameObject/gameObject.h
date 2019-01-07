#pragma once
#include <list>
#include <vector>
#include <set>
#include "Component/component.h"
#include "System\Physics\collision.h"
#include "System\Physics\rayCastHit.h"

//Game objects by default are empty. Components can be added to them to create behaviour.
//Only one of each component can be held.
class GameObject {

public:

    //Constructor adds object to list of all gameObjects in gameLogic
    GameObject(std::string _name = "");

    //Destructor deletes all components
    ~GameObject();

    //Calls start() for all objects in all_gameobjects *NOTE* Should not be public, preferably the caller should be friend of GameObject
    static void startAll();
    //Call onActivate() for all objects in just_activated_gameobjects
    //Call onDeactivate() for all objects in just_deactivated_gameobjects
    //and update() lateUpdate() for all active objects in all_gameObjects *NOTE* Should not be public, preferably the caller should be friend of GameObject
    static void updateAll();
    //Call lateUpdate() for all active objects in all_gameObjects
    //Should be called after physics calculations *NOTE* Should not be public, preferably the caller should be friend of GameObject
    static void lateUpdateAll();


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
    inline bool getActive() const { return active; }
    //sets active
    void setActive(bool b);

    inline std::string getName() const { return name; }

    //THESE COLLISION-METHODS SHOULD ONLY BE ACCESSIBLE BY PHYSICSENGINE
    //THIS NEEDS TO BE FIXED
    //ALSO, WHY ARE THEY VIRTUAL?
    //Calls onCollisionEnter() on all components
    virtual void onCollisionEnter(Collision *collision);
    //Calls onColliding() on all components
    virtual void onColliding(Collision *collision);
    //Calls onCollisionExit() on all components
    virtual void onCollisionExit();
    
    //Calls rayHit() on all components
    virtual void rayHit(RayCastHit* hit);

    void setArgs(std::vector<double> _args);
    inline std::vector<double> getArgs() const { return args; }

private:
    //Call start() in every component
    void start();
    //Call onActivate() in every component
    void onActivate();
    //Call onDeactivate() in every component
    void onDeactivate();
    //Call update() in every component
    void update();
    //Call lateUpdate() in every component
    void lateUpdate();

    //Updates all components references
    void updateComponents();



    //Components contained by this gameobject
    std::list<Component*> components;

    //If active, this gameObject will be updates each frame
    bool active;

    //List of all gameObjects
    static std::set<GameObject*> all_gameObjects;
    //List of all gameObjects that turned active this frame
    static std::set<GameObject*> just_activated_gameObjects;
    //List of all gameObjects that turned inactive this frame
    static std::set<GameObject*> just_deactivated_gameObjects;

    std::string name;

protected:
    //arguments that can be used at any time
    //suggested use is in awake() after pool instantiation
    std::vector<double> args;
};


//Get component of component type T. If none is present, null is return
template<class T>
T * GameObject::getComponent()
{
    if (!std::is_base_of<Component, T>::value) {
        throw std::invalid_argument("Expected Component Type");
        //return NULL; //Unreachable
    }

    for each  (Component *t in components)
    {
        if (dynamic_cast<T*>(t)) {
            return (T*)t;
        }
    }

    return NULL;
}

//Adds component of type T. If one is already present it is replaced
template<class T>
T * GameObject::addComponent()
{

    if (!std::is_base_of<Component, T>::value) {
        throw std::invalid_argument("Expected Component Type");
        return NULL;
    }

    removeComponent<T>();

    T *component = new T(this);

    components.push_back(component);

    updateComponents();

    return component;
}

//Removes component of type T.
template<class T>
void * GameObject::removeComponent()
{

    if (!std::is_base_of<Component, T>::value) {
        throw std::invalid_argument("Expected Component Type");
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

//Checks if gameObject has component of type T.
template<class T>
bool GameObject::hasComponent()
{
    if (!std::is_base_of<Component, T>::value) {
        throw std::invalid_argument("Expected Component Type");
    }

    for each  (Component *t in components)
    {
        if (dynamic_cast<T*>(t)) {
            return true;
        }
    }
    return false;
}
