#pragma once
#include "lTexture.h"
#include <vector>
#include "math\polygon.h"
#include <string>

class TileMap {
    public:
    TileMap();
    ~TileMap();
    //Tile map Texture
    LTexture texture;
    //Matrix denoting colliders corresponding to the tile map
    std::vector<std::vector<Polygon>> colliderMatrix;

    void loadFromFile(std::string texturePath, std::string colliderPath);
};