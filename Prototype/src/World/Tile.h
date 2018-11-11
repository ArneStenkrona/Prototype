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
    Tile(int _tileIndex = -1, int _rotation = 0, bool _flipH = false, bool _flipV = false, std::optional<Polyshape> _polygon = {}, int _objectIndex = -1);

    ~Tile();

    static const unsigned int TILE_SIZE;
    static const unsigned int TILES_PER_ROW;
    static const unsigned int TILES_PER_COLUMN;

    bool hasCollider() const;
    void setPolygon(std::optional<Polyshape> p) { polygon = p; };
    Polyshape *getPolygon();
    int getIndex();
    inline int getRotation() { return rotation; }
    inline void getFlip(bool &_flipH, bool &_flipV) { _flipH = flipH; _flipV = flipV; }

    inline int getObject() const { return objectIndex; }
    inline void setObject(int index) { objectIndex = index; }

    GameObject* gameObjectFromTile(int x, int y) const;
    //Instantiates the object contained by this tile, if any, else returns null
    GameObject* instantiateObject(int x, int y) const;

    //Renders tile at coordinates (x, y)
    void renderTile(int x, int y);

private:
    //Defines texture within the tileset
    int tileIndex;
    //Collider shape, if present
    std::optional<Polyshape> polygon;
    //Index of object to be instantiated, as defined in object.h, -1 if not present;
    int objectIndex;
    //multiples of 90 degree rotation
    int rotation;
    bool flipH;
    bool flipV;
};