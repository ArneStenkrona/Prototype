#include "polygon.h"


Polygon::~Polygon()
{
    vertices.clear();
}

void Polygon::setDimensions()
{
    double minX = vertices[0].x, maxX = vertices[0].x;
    double minY = vertices[0].y, maxY = vertices[0].y;

    for (int i = 0; i < numberOfVertices; i++) {
        if (vertices[i].x < minX) {
            minX = vertices[i].x;
        }
        else if (vertices[i].x > maxX) {
            maxX = vertices[i].x;
        }

        if (vertices[i].y < minY) {
            minY = vertices[i].y;
        }
        else if (vertices[i].y > maxY) {
            maxY = vertices[i].y;
        }
    }

    _width = maxX - minX;
    _height = maxY - minY;


}
