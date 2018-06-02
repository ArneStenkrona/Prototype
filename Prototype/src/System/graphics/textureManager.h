#pragma once
#include "lTexture.h"
#include <SDL.h>
#include <vector>
#include <string>
#include "math\polygon.h"
#include "TileMap.h"

//This file takes care of input for controls
//Might want to make this into a static class
class TextureManager {

public:

    static enum TILE_TEXTURE_NAMES
    {
        DEFAULT_TILE_TEXTURE,
        FLOOR,
        WALL,
        WALL_BASE,
        ROCK_0_075,
        ROCK_075_1,
        TOTAL_TILE_TEXTURES
    };

    static enum BACKGROUND_TEXTURE_NAMES
    {
        DEFAULT_BACKGROUND_TEXTURE,
        TOTAL_BACKGROUND_TEXTURES
    };

    //Corresponds to mapPaths
    static enum TILEMAPS {
        LAB_MAP,
        TOTAL_MAPS
    };

    static void initalizeTextureManager();

    //Loads textures into tileset
    //Path must refer to a 512*512 png image.
    //Tileset images are sets of 16*16 tiles each being 32*32 pixels
    //The lower half of the tileset is resereved for tiles without hitboxes
    static void loadTileSet(TILEMAPS map);

    //Vector of all tile textures
    static std::vector<LTexture> tile_textures;
    //Vector of all background textures
    static std::vector<LTexture> background_textures;

    //Misc textures
    static std::vector<LTexture> miscallenous;

    //Current tilemap
    static TileMap tileMap;

    //Should only be closed when application exits
    static void closeTextureManager();

private:
    //Filepaths of all the tilemaps
    static const std::string mapPaths[TOTAL_MAPS];
    //Filepaths of all the corresponding collider matrices
    static const std::string colliderPaths[TOTAL_MAPS];

    //Generates and returns an SDL_Rect for a tile at the given index (assuming a tilesheet arranged in 16*16)
    static SDL_Rect generateTileQuad(unsigned int index);


};
