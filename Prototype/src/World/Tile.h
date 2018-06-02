#pragma once
#include "math/polygon.h"
#include "GameObject\gameObject.h"
#include <optional>

/*
    A level is comprised of tiles.
    A tile is a 32 x 32 pixel square
*/
class Tile {
public:
    Tile(int _tileIndex);
    Tile(int _tileIndex, Polyshape _polygon);
    ~Tile();

    bool hasCollider();
    Polyshape *getPolygon();
    int getIndex();

    GameObject* gameObjectFromTile(int x, int y);

    //Renders tile at coordinates (x, y)
    void renderTile(int x, int y);

private:
    //Defines texture within the tileset
    int tileIndex;
    //Collider shape, if present
    optional<Polyshape> polygon;

};