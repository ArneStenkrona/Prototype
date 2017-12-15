#pragma once
#include "GameObject/Component/component.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"

class GameObject;
class Movement : public Component {
public:
    Movement(GameObject *_object);
    void start();
    void update();
    void updateComponents();

    //Maximum speed (compares to velocity.magnitude())
    double speed = 10;
    //acceleration factor [0,inf[
    double acceleration = 1;
    //Drag factor [0,1]
    double drag = 0.9;

private:
    Position *position;
    Velocity *velocity;




};