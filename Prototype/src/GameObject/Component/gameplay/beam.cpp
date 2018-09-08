#include "beam.h"
#include "GameObject\gameObject.h"

Beam::Beam(GameObject * _object) : Component(_object), counter(-1)
{
    lineRenderer = requireComponent<LineRenderer>();
}

void Beam::start()
{
}

unsigned char colors[] = { 0, 50, 100, 150, 200, 255 };

void Beam::update()
{
    if (counter > -1) {
        lineRenderer->setColor(255, colors[counter], colors[counter], colors[counter]);
        counter--;
    }
}

void Beam::updateComponents()
{
    lineRenderer = (object->hasComponent<LineRenderer>()) ? object->getComponent<LineRenderer>() : lineRenderer;
}

void Beam::setPoints(Point a, Point b)
{
    lineRenderer->a = a;
    lineRenderer->b = b;
    lineRenderer->thickness = 3;
    lineRenderer->setColor(255, 255, 255, 255);
    counter = 5;
}
