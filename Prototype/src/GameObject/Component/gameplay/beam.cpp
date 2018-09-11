#include "beam.h"
#include "GameObject\gameObject.h"
#include "GameObject\objectPool.h"

Beam::Beam(GameObject * _object) : Component(_object), counter(0), contraction(50)
{
    lineRenderer = requireComponent<LineRenderer>();
}

bool woke = false;
void Beam::onActivate()
{
    std::vector<double> args = object->getArgs();
    if (args.size() >= 4)
        setPoints(Point(args[0], args[1]), Point(args[2], args[3]));
    lineRenderer->thickness = 3;
    lineRenderer->setColor(255, 255, 255, 255);
    counter = 5;
    woke = true;
}

void Beam::start()
{
    lineRenderer->setColor(0,0,0,0);
    lineRenderer->a = Point(0, 0);
    lineRenderer->b = Point(0,0);
}

unsigned char colors[] = { 0, 50, 100, 150, 200, 255 };

void Beam::update()
{
    if (counter > -1) {
        if (contraction) {
            Point a = lineRenderer->a;
            Point b = lineRenderer->b;
            if (a.distanceTo(b) > contraction) {
                Point direction = (b - a).normalized();
                lineRenderer->a += direction * contraction;
            }
            else {
                lineRenderer->setColor(0, 0, 0, 0);
                counter = -1;
            }
        }
        lineRenderer->setColor(255, colors[counter], colors[counter], colors[counter]);
        counter--;
    }
    else if (woke) {
        ObjectPool::repool(object);
        woke = false;
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
}
