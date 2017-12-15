#include "rectangle.h"

Rectangular::Rectangular(Point a, double _width, double _height)
{

    numberOfVertices = 4;

    vertices.push_back(a);
    vertices.push_back(Point(a.x + _width, a.y));
    vertices.push_back(Point(a.x + _width, a.y + _height));
    vertices.push_back(Point(a.x, a.y + _height));

    setDimensions();
}

Rectangular::Rectangular(Point a, Point b, Point c, Point d)
{
    numberOfVertices = 4;

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    vertices.push_back(d);

    setDimensions();
}
