#pragma once
#include "GameObject/gameObject.h"
#include "System/graphics/lTexture.h"
#include "math/polygon.h"

//Stores Tile information. Helps with saving
struct Tile {
    //Position in the room
    int x, y;
    //Defines texture within the tileset
    int tileIndex;
    bool hasCollider;
    //Collider shape
    Polygon polygon;
};

//The screen is divided into a 16 x 9 tilegrid. 
//This means that a single tile is a 32x32 pixel image.
//This tile size dictates positions of objects

//Creates a gameObject as defined by the tile
GameObject *createTile(Tile tile);

