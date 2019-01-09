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

    enum BACKGROUND_TEXTURE_NAMES
    {
        DEFAULT_BACKGROUND_LAYER,
        TOTAL_BACKGROUND_TEXTURES
    };

    //Corresponds to mapPaths
    enum TILEMAPS {
        LAB_MAP,
        DUNGEON_MAP,
        TOTAL_MAPS
    };

    enum SPRITE_SHEETS {
        PRT,
        OBJECTS_1,
        OBJECT_ICONS,
        TOOL_ICONS,
        TOTAL_SPRITE_SHEETS
    };

    enum FONT_TEXTURES
    {
        FONT1,
        TOTAL_FONTS
    };

    static void initalizeTextureManager();
    //Should only be closed when application exits
    static void closeTextureManager();

    //Loads textures into tileset
    //Path must refer to a 512*512 png image.
    //Tileset images are sets of 16*16 tiles each being 32*32 pixels
    //The lower half of the tileset is resereved for tiles without hitboxes
    static void loadTileSet(TILEMAPS map);

    //Vector of all background textures
    static std::vector<std::vector<LTexture>> background_layer_textures;

    //Misc textures
    static std::vector<LTexture> miscellaneous;

    //Vector of all sprite sheets
    static std::vector<LTexture> spriteSheets;

    //Vector of all font textures
    static std::vector<LTexture> fontTextures;


    //Current tilemap
    static TileMap tileMap;


private:
    //Filepaths of all the tilemaps
    static const std::string mapPaths[TOTAL_MAPS];
    //Filepaths of all the corresponding collider matrices
    static const std::string colliderPaths[TOTAL_MAPS];
    //Filepaths of all sprite sheets
    static const std::string sheetPaths[TOTAL_SPRITE_SHEETS];

    //Filepaths of all font textures
    static const std::string fontPaths[TOTAL_FONTS];

    //Generates and returns an SDL_Rect for a tile at the given index (assuming a tilesheet arranged in 16*16)
    static SDL_Rect generateTileQuad(unsigned int index);


};
