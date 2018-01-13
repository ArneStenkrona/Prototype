#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits.h>

Polygon::~Polygon()
{
    vertices.clear();
}

double Polygon::distanceTo(Point p)
{
    double d = DBL_MAX;
    for (int i = 0; i < numberOfVertices - 1; i++) {
        double r = Point(vertices[i + 1] - vertices[i]).dot(Point(p - vertices[i]));

        r /= Point(p - vertices[i]).magnitude();
        double distance;
        if (r < 0.0) {
            distance = Point(p - vertices[i]).magnitude();
        }
        else if (r > 1.0) {
            distance = Point(vertices[i + 1] - p).magnitude();
        }
        else {
            distance = sqrt(pow(Point(p - vertices[i]).magnitude(), 2) - r * pow(Point(vertices[i + 1] - vertices[i]).magnitude(), 2));
        }
        if (distance < d) d = distance;
    }
    return d;
}

void Polygon::setDimensions()
{
    double minX = vertices[0].x, maxX = vertices[0].x;
    double minY = vertices[0].y, maxY = vertices[0].y;

    for (int i = 0; i < numberOfVertices; i++) {
        if (vertices[i].x < minX) {
            minX = vertices[i].x;
        }
        if (vertices[i].x > maxX) {
            maxX = vertices[i].x;
        }

        if (vertices[i].y < minY) {
            minY = vertices[i].y;
        }
        if (vertices[i].y > maxY) {
            maxY = vertices[i].y;
        }
    }

    _width = std::abs(maxX - minX);
    _height = std::abs(maxY - minY);


}
