#pragma once
#include "../component.h"
#include "math/point.h"

class GameObject;
class Position : public Component {
public:
    Position(GameObject *_object);
    Position(GameObject *_object, Point _position);
    Point position;
};