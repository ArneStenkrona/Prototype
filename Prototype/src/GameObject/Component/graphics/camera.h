#pragma once
#include "../geometry/position.h"
#include "../component.h"
#include "GameObject/gameObject.h"

//The main camera determines the relative position to which everything is rendered
class Camera : public Component {
public:
    Camera(GameObject *_object);
    Point velocity;
    void start();
    void update();
    void updateComponents();

    void setTarget(GameObject *targetObject);

    inline Position *getPosition() const { return position; }

    //The target which the camera aims at
    GameObject *target;

private:
    Position *position;
    //Position of the target
    Position *targetPosition;
    //Bounds of the target
    Point targetBounds;
    //Point storing the offset necessary to center the target in the window
    static const Point screenOffset;

};