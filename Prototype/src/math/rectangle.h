#pragma once
#include "polygon.h"

//Rectangle name already in windows namespace
class Rectangular : public Polyshape {
public:
    Rectangular(Point a, double _width, double _height);
    Rectangular(Point a, Point b, Point c, Point d);
};