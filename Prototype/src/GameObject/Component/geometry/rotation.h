#pragma once
#include "../component.h"

class GameObject;
class Rotation : public Component {
public:
    Rotation(GameObject *_object);
    //rotation angle in degrees
    double rotation;
    Point pivot;
};