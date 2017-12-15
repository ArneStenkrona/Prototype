#include "textureManager.h"
#include <string>

std::vector<LTexture> TextureManager::tile_textures;
std::vector<LTexture> TextureManager::background_textures;

LTexture TextureManager::active_tileset = LTexture();

const std::string TextureManager::mapPaths[TextureManager::TOTAL_MAPS] = { "Assets/Textures/Laboratory/TILEMAP_LAB.png" };

void TextureManager::initalizeTextureManager()
{

    tile_textures.resize(TOTAL_TILE_TEXTURES);

    for (int i = 0; i < TOTAL_TILE_TEXTURES; i++) {
        tile_textures.push_back(LTexture());
    }

    //Load all textures
    tile_textures[DEFAULT_TILE_TEXTURE].loadFromFile("Assets/textures/Default/default texture.png");
    tile_textures[FLOOR].loadFromFile("Assets/textures/laboratory/floor.png");
    tile_textures[WALL].loadFromFile("Assets/textures/laboratory/wall.png");
    tile_textures[WALL_BASE].loadFromFile("Assets/textures/laboratory/wall base.png");
    tile_textures[ROCK_0_075].loadFromFile("Assets/textures/laboratory/rock_0-075.png");
    tile_textures[ROCK_075_1].loadFromFile("Assets/textures/laboratory/rock_075-1.png");


    background_textures.resize(TOTAL_BACKGROUND_TEXTURES);

    for (int i = 0; i < TOTAL_BACKGROUND_TEXTURES; i++) {
        background_textures.push_back(LTexture());
    }

    background_textures[DEFAULT_BACKGROUND_TEXTURE].loadFromFile("Assets/textures/Backgrounds/purple background.png");

}

void TextureManager::loadTileSet(TILEMAPS map)
{
    if (map >= TOTAL_MAPS) {
        return;
    }


    active_tileset.loadFromFile(mapPaths[map]);
}

SDL_Rect TextureManager::generateTileQuad(unsigned int index)
{

    SDL_Rect tileQuad;

    tileQuad.x = 32 * (index % 16);
    tileQuad.y = 32 * (index / 16);
    tileQuad.w = 32;
    tileQuad.h = 32;


    return tileQuad;
}

void TextureManager::closeTextureManager()
{
    for (int i = 0; i < TOTAL_TILE_TEXTURES; i++) {
        tile_textures[i].free();
    }

    for (int i = 0; i < TOTAL_BACKGROUND_TEXTURES; i++) {
        background_textures[i].free();
    }

    active_tileset.free();

}

