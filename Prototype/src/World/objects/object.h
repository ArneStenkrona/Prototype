#pragma once
//Class for objects that can be placed in the game
//Useful abstraction for editor
#include "GameObject\Prefabrications\prefabrication.h"

class Object {
public:
    //Predefined
    static const Object objects[256];
    //Instantiate prefab;
    GameObject* instantiate() const;
private:
    Object(Prefabrication _prefab);
    Object();
    Prefabrication prefab;
};
