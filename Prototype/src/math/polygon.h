#pragma once
#include "point.h"
#include <vector>
#include <string>

//Base class for polygons
//Vertices are point relative to the position of the gameObject which contains this polygon
class Polygon {
public:
    ~Polygon();
    //These should not be public, or at least not mutable
    std::vector<Point> vertices;
    size_t numberOfVertices;

    //Dimensions of the shape
    double _width;
    double _height;
    //Returns the distance between this polygon and a point
    double distanceTo(Point p);

    //Parses a string and creates a polygon
    static Polygon parsePolygon(std::string s);

protected:
    //This sets the dimensions of the shape
    //Should be called everytime the shape is altered
    void setDimensions();


};