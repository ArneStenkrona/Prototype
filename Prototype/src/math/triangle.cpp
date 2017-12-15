#include "triangle.h"

Triangle::Triangle(Point a, Point b, Point c)
{
    numberOfVertices = 3;

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);

    setDimensions();
}
