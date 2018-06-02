#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include "tools\stringTools.h"
#include <vector>
#include "triangle.h"
#include "rectangle.h"


Polyshape::~Polyshape()
{
    vertices.clear();
}

double Polyshape::distanceTo(Point p)
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

Polyshape Polyshape::parsePolygon(std::string s)
{
    if (s == "B") return Rectangular(Point(0.0, 0.0), Point(0.0, 32.0), Point(32.0,32.0), Point(32.0, 0.0));


    Polyshape polygon;

    s.erase(0, 1);
    s.pop_back();
    //separate by points
    std::vector<std::string> pointStrings = brokenStringSplitter(s, ')');
    pointStrings.pop_back();

    std::vector<Point> points;
    for (int k = 0; k < pointStrings.size(); k++) {
        std::vector<std::string> doubles = brokenStringSplitter(pointStrings[k], ',');
        points.push_back(Point(atof(doubles[0].c_str()), atof(doubles[1].c_str())));
    }

    if (points.size() == 3) {
        polygon = Triangle(points[0], points[1], points[2]);

    }
    else if (points.size() == 4){
        polygon = Rectangular(points[0], points[1], points[2], points[3]);
    }
    return polygon;
}

void Polyshape::setDimensions()
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
