#pragma once
#include "point.h"
#include <vector>
#include <string>
#include "System\graphics\color.h"

//Base class for polygons
//I did not want it to be named Polyshape, but windows.h has overzealous definitions
//Vertices are point relative to the position of the gameObject which contains this polygon
class Polyshape {
public:
    ~Polyshape();
    //These should not be public, or at least not mutable
    std::vector<Point> vertices;
    size_t numberOfVertices;

    //Dimensions of the shape
    //Really shouldn't be public
    double _width;
    double _height;
    //Returns the distance between this polygon and a point
    double distanceTo(Point p);

    //Geometric centre of the polygon
    //Arithmetic mean
    Point geometricCenter();

    //A point where x value is the average of the leftmost vertex x and the rightmost vertex x
    //and y value is the average of the highest vertex y and the lowest vertex by
    Point center();
    
    //gets a point such that a rectangle with dimensions _width*_height
    //centered at this point would surround the polygon
    Point getEffectiveOrigin();
    //Point vertexClosestToOrigin();

    //Parses a string and creates a polygon
    static Polyshape parsePolygon(std::string s);

    //Renders the outline of the polygon
    void renderPolygon(int x, int y, Color color = COLOR_PURPLE);

    std::string toString();

    //Basic polygons, useful for making colliders
    static std::vector<Polyshape> basicPolygons;
protected:
    //This sets the dimensions of the shape
    //Should be called everytime the shape is altered
    void setDimensions();
    //Point where x-coordinate is x-coord of leftmost vertex
    //and y-coordinate is y-coord of topmost vertex
    Point effectiveOrigin;
};