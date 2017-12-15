#pragma once
#include "polygon.h"

//Rectangle name was taken by piece of shit microsoft fuckface class
class Rectangular : public Polygon {
public:
    Rectangular(Point a, double _width, double _height);
    Rectangular(Point a, Point b, Point c, Point d);
};