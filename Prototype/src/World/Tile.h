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
    Tile(int _tileIndex = -1, int _rotation = 0, bool _flipH = false, bool _flipV = false, 
        std::optional<Polyshape> _polygon = {}, int _objectIndex = -1, std::vector<std::string> _objectparameters = {});

    ~Tile();

    static const size_t TILE_SIZE;
    static const size_t TILES_PER_ROW;
    static const size_t TILES_PER_COLUMN;
    //Cash for converting tile dimension to pixel dimension
    static const unsigned int tileToPixel[16];

    bool hasCollider() const;
    void setPolygon(std::optional<Polyshape> p) { polygon = p; };
    Polyshape *getPolygon();
    int getIndex();
    inline int getRotation() { return rotation; }
    inline void getFlip(bool &_flipH, bool &_flipV) { _flipH = flipH; _flipV = flipV; }

    inline int getObject() const { return objectIndex; }
    //Sets the object index
    void setObject(int index, std::vector<std::string> parameters = {});
    
    std::vector<std::string> getObjectParameters() const { return objectParameters; }

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
    //Parameters sent to the object when instantiated
    std::vector<std::string> objectParameters;
    //multiples of 90 degree rotation
    int rotation;
    bool flipH;
    bool flipV;
};