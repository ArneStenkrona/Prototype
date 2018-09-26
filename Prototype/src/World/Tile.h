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
    Tile(int _tileIndex, int _rotation, bool _flipH, bool _flipV);
    Tile(int _tileIndex, std::optional<Polyshape> _polygon);
    Tile(int _tileIndex, std::optional<Polyshape> _polygon, int _rotation, bool _flipH, bool _flipV);

    ~Tile();

    static const unsigned int TILE_SIZE;

    bool hasCollider();
    void setPolygon(Polyshape p) { if (polygon) polygon = p; };
    Polyshape *getPolygon();
    int getIndex();
    inline int getRotation() { return rotation; }
    inline void getFlip(bool &_flipH, bool &_flipV) { _flipH = flipH; _flipV = flipV; }

    GameObject* gameObjectFromTile(int x, int y);

    //Renders tile at coordinates (x, y)
    void renderTile(int x, int y);

private:
    //Defines texture within the tileset
    int tileIndex;
    //Collider shape, if present
    std::optional<Polyshape> polygon;
    //multiples of 90 degree rotation
    int rotation;
    bool flipH;
    bool flipV;
};