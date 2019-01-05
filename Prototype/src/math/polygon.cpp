#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include "tools\stringTools.h"
#include <vector>
#include <SDL_image.h>
#include "System\graphics\graphicsEngine.h"
#include <math.h> 

std::vector<Polyshape> Polyshape::basicPolygons = {
    Polyshape(Tile::TILE_SIZE, Tile::TILE_SIZE, Point(0,0)),
    Polyshape({ Point(0, 0), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(0, Tile::TILE_SIZE) }),
    Polyshape({ Point(Tile::TILE_SIZE, 0), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(0, Tile::TILE_SIZE) }),
    Polyshape({ Point(0, 0), Point(Tile::TILE_SIZE, 0), Point(0, Tile::TILE_SIZE) }),
    Polyshape({ Point(Tile::TILE_SIZE, 0), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(0, 0) }),
    Polyshape({ Point(Tile::TILE_SIZE - (Tile::TILE_SIZE / 4), 0), Point(Tile::TILE_SIZE, 0), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(Tile::TILE_SIZE - (Tile::TILE_SIZE / 4), Tile::TILE_SIZE) }),
    Polyshape({ Point(0, 0), Point((Tile::TILE_SIZE / 4), 0), Point((Tile::TILE_SIZE / 4), Tile::TILE_SIZE), Point(0, Tile::TILE_SIZE) }),
    Polyshape({ Point(0, Tile::TILE_SIZE / 2), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(0, Tile::TILE_SIZE) }),
    Polyshape({ Point(Tile::TILE_SIZE - (Tile::TILE_SIZE / 4), Tile::TILE_SIZE - (Tile::TILE_SIZE / 4) - Tile::TILE_SIZE / 16), Point(Tile::TILE_SIZE, 22), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(Tile::TILE_SIZE / 4, Tile::TILE_SIZE) }),
    Polyshape({Point(0, Tile::TILE_SIZE - (Tile::TILE_SIZE / 4) - Tile::TILE_SIZE / 16), Point(Tile::TILE_SIZE / 2, Tile::TILE_SIZE), Point(Tile::TILE_SIZE, Tile::TILE_SIZE)}),
    Polyshape({Point(0,  Tile::TILE_SIZE + 0.75), Point(Tile::TILE_SIZE,  Tile::TILE_SIZE / 4), Point(Tile::TILE_SIZE,  Tile::TILE_SIZE)}),
    Polyshape({Point(0,  Tile::TILE_SIZE / 4), Point(Tile::TILE_SIZE, 0), Point(Tile::TILE_SIZE,  Tile::TILE_SIZE)})
};

Polyshape::Polyshape(std::vector<Point> _vertices)
    : vertices(_vertices)
{
    numberOfVertices = vertices.size();
    setDimensions();
}

Polyshape::Polyshape(std::initializer_list<Point> _vertices)
    : vertices(_vertices)
{
    numberOfVertices = vertices.size();
    setDimensions();
}

Polyshape::Polyshape(double _width, double _height, Point a)
    : Polyshape({a,
                 Point(a.x + _width, a.y),
                 Point(a.x + _width, a.y + _height),
                 Point(a.x, a.y + _height)})
{
}

Polyshape::~Polyshape()
{
    vertices.clear();
}

double Polyshape::distanceTo(Point p)
{
    double d = DBL_MAX;
    for (unsigned int i = 0; i < numberOfVertices - 1; i++) {
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
    for (unsigned int i = 0; i < vertices.size(); i++) {
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

    for (unsigned int i = 0; i < vertices.size(); i++) {
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

Polyshape Polyshape::rotate(double angle, Point pivot)
{
    Polyshape pg = *this;

    for (unsigned int i = 0; i < pg.vertices.size(); i++) {
        pg.vertices[i] = pg.vertices[i].rotate(angle, pivot);
    }

    return pg;
}

Polyshape Polyshape::mirror(bool horizontal, bool vertical, Point offset)
{
    Polyshape pg = *this;

    for (unsigned int i = 0; i < pg.vertices.size(); i++) {
        if (horizontal)
            pg.vertices[i].x = offset.x - pg.vertices[i].x;
        if (vertical)
            pg.vertices[i].y = offset.y - pg.vertices[i].y;
    }

    return pg;
}

Polyshape Polyshape::parsePolygon(std::string s)
{
    if (s == "B") return Polyshape({ Point(0.0, 0.0), Point(0.0, Tile::TILE_SIZE), Point(Tile::TILE_SIZE, Tile::TILE_SIZE), Point(Tile::TILE_SIZE, 0.0) });

    s.erase(0,1);
    s.pop_back();
    std::vector<Point> points;
    std::vector<std::string> pointStrings = stringSplitter(s, ')');
    for (unsigned int i = 0; i < pointStrings.size(); i++) {

        pointStrings[i].erase(0,1);
        std::vector<std::string> doubles = stringSplitter(pointStrings[i], ',');
        points.push_back(Point(atof(doubles[0].c_str()), atof(doubles[1].c_str())));
    }
    return Polyshape(points);
}

void Polyshape::renderPolygon(int x, int y, Color color)
{
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    for (unsigned int i = 0; i < vertices.size(); i++) {
        //Weird code that makes sure polygons are drawn contained within its dimensions
        int a = (int)(abs(vertices[i].x) >= (int)(width) ? vertices[i].x - 1 : vertices[i].x) + x;
        int b = (int)(abs(vertices[i].y) >= (int)(height) ? vertices[i].y - 1 : vertices[i].y) + y;
        int c = (int)(abs(vertices[(i + 1) % vertices.size()].x) >= (int)width ?
                 vertices[(i + 1) % vertices.size()].x - 1 : vertices[(i + 1) % vertices.size()].x) + x;
        int d = (int)(abs(vertices[(i + 1) % vertices.size()].y) >= (int)height ?
            vertices[(i + 1) % vertices.size()].y - 1 : vertices[(i + 1) % vertices.size()].y) + y;
        SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(), a, b, c, d);
    }
}

std::string Polyshape::toString()
{
    std::string s = "<";

    for (unsigned int i = 0; i < vertices.size(); i++) {
        s += vertices[i].toString() + ",";
    }
    s += ">";

    return s;
}

void Polyshape::setDimensions()
{
    double minX = vertices[0].x, maxX = vertices[0].x;
    double minY = vertices[0].y, maxY = vertices[0].y;

    for (unsigned int i = 0; i < numberOfVertices; i++) {     
            minX = std::min(minX, vertices[i].x);
            maxX = std::max(maxX, vertices[i].x);
            minY = std::min(minY, vertices[i].y);
            maxY = std::max(maxY, vertices[i].y);
    }
    effectiveOrigin = Point(minX,minY);
    width = std::abs(maxX - minX);
    height = std::abs(maxY - minY);
}
