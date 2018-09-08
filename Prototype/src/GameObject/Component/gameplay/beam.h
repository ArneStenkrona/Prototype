#pragma once
#include "GameObject\Component\component.h"
#include "GameObject\Component\graphics\lineRenderer.h"

class GameObject;
class Beam : public Component {
public:
    Beam(GameObject *_object);
    void start();
    void update();
    void updateComponents();

    void setPoints(Point a, Point b);

private:
    LineRenderer* lineRenderer;
    int counter;
};