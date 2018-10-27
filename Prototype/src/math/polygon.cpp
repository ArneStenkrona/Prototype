#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include "tools\stringTools.h"
#include <vector>
#include "triangle.h"
#include "rectangle.h"
#include <SDL_image.h>
#include "System\graphics\graphicsEngine.h"

std::vector<Polyshape> Polyshape::basicPolygons = { 
    Rectangular(Point(0, 0), 32, 32),
    Triangle(Point(0, 0), Point(32, 32), Point(0, 32)),
    Triangle(Point(32, 0), Point(32, 32), Point(0, 32)),
    Triangle(Point(0, 0), Point(32, 0), Point(0, 32)),
    Triangle(Point(32, 0), Point(32, 32), Point(0, 0)),
    Rectangular(Point(24, 0), Point(32, 0), Point(32, 32), Point(24, 32)),
    Rectangular(Point(0, 0), Point(8, 0), Point(8, 32), Point(0, 32)),
    Triangle(Point(0, 16), Point(32, 32), Point(0, 32)),
    Rectangular(Point(24, 22), Point(32, 22), Point(32, 32), Point(8, 32)),
    Triangle(Point(0, 22), Point(16, 32), Point(32, 32)),
    Triangle(Point(0, 32.75), Point(32, 8), Point(32, 32)),
    Triangle(Point(0, 8), Point(32, 0), Point(32, 32))
};

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

Point Polyshape::geometricCenter()
{
    double sumX = 0.0;
    double sumY = 0.0;
    for (int i = 0; i < vertices.size(); i++) {
        sumX += vertices[i].x;
        sumY += vertices[i].y;
    }

    return Point(sumX / numberOfVertices, sumY / numberOfVertices);
}

Point Polyshape::center()
{
    double leftMostX = vertices[0].x;
    double rightMostX = vertices[0].x;
    double highestY = vertices[0].y;
    double lowestY = vertices[0].y;

    for (int i = 0; i < vertices.size(); i++) {
        leftMostX = std::min(leftMostX, vertices[i].x);
        rightMostX = std::max(rightMostX, vertices[i].x);
        highestY = std::min(highestY, vertices[i].y);
        lowestY = std::max(lowestY, vertices[i].y);
    }


    return Point((leftMostX + rightMostX) / 2, (highestY + lowestY) / 2);
}

Point Polyshape::getEffectiveOrigin()
{
    return effectiveOrigin;
}

Polyshape Polyshape::parsePolygon(std::string s)
{
    if (s == "B") return Rectangular(Point(0.0, 0.0), Point(0.0, 32.0), Point(32.0, 32.0), Point(32.0, 0.0));
    Polyshape polygon;

    s.erase(0,1);
    s.pop_back();
    std::vector<Point> points;
    std::vector<std::string> pointStrings = stringSplitter(s, ')');
    for (int i = 0; i < pointStrings.size(); i++) {
        pointStrings[i].erase(0,1);
        std::vector<std::string> doubles = stringSplitter(pointStrings[i], ',');
        points.push_back(Point(atof(doubles[0].c_str()), atof(doubles[1].c_str())));
    }

    if (points.size() == 3) {
        polygon = Triangle(points[0], points[1], points[2]);

    }
    else if (points.size() == 4) {
        polygon = Rectangular(points[0], points[1], points[2], points[3]);
    }
    return polygon;
}

void Polyshape::renderPolygon(int x, int y)
{
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), 255, 0, 255, 255);
    for (int i = 0; i < vertices.size(); i++) {
        SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(), vertices[i].x + x, vertices[i].y + y,
                vertices[(i + 1) % vertices.size()].x + x, vertices[(i + 1) % vertices.size()].y + y);
    }
}

std::string Polyshape::toString()
{
    std::string s = "<";

    for (int i = 0; i < vertices.size(); i++) {
        s += vertices[i].toString() + ",";
    }
    s += ">";

    return s;
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
    effectiveOrigin = Point(minX,minY);
    _width = std::abs(maxX - minX);
    _height = std::abs(maxY - minY);


}
