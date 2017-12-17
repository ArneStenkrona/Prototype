#pragma once
#include "math/polygon.h"
#include "GameObject\gameObject.h"
/*
    A level is comprised of tiles.
    A tile is a 32 x 32 pixel square
*/
class Tile {
public:
    Tile(int _tileIndex);
    Tile(int _tileIndex, Polygon _polygon);
    ~Tile();

    bool hasCollider();
    Polygon *getPolygon();
    int getIndex();

    GameObject* gameObjectFromTile(int x, int y);

private:
    //Defines texture within the tileset
    int tileIndex;
    //Does the tile have a collider?
    bool collider;
    //Collider shape
    Polygon polygon;

};