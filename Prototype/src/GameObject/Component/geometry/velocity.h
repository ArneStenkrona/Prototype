#pragma once
#include "../component.h"
#include "position.h"

class Velocity : public Component {
public:
    Velocity(GameObject *_object);
    Point velocity;
    void start();
    void update();
    void updateComponents();
private:
    Position *position;



};
