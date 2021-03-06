#pragma once
#include "lTexture.h"
#include <vector>
#include <string>
#include <optional>
#include "math\polygon.h"

//Data structure holding the texture of a tile map and the collision data
class TileMap {
    public:
    TileMap();
    ~TileMap();
    //Tile map Texture
    LTexture texture;
    //Matrix denoting colliders corresponding to the tile map
    std::vector<std::vector<std::optional<Polyshape>>> colliderMatrix;

    void loadFromFile(std::string texturePath, std::string colliderPath);
};