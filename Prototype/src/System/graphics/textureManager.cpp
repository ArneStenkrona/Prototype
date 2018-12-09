#include "textureManager.h"
#include <string>
#include "graphicsEngine.h"

std::vector<std::vector<LTexture>> TextureManager::background_layer_textures;
std::vector<LTexture> TextureManager::miscellaneous;
std::vector<LTexture> TextureManager::spriteSheets;
std::vector<LTexture> TextureManager::fontTextures;

const std::string TextureManager::mapPaths[TextureManager::TOTAL_MAPS] = { "Assets/textures/laboratory/TILEMAP_LAB.png" };
const std::string TextureManager::colliderPaths[TextureManager::TOTAL_MAPS] = { "Assets/textures/laboratory/TILEMAP_LAB.col" };
const std::string TextureManager::sheetPaths[TextureManager::TOTAL_SPRITE_SHEETS] = { "Assets/Sprites/prt/prt.png",
                                                                                      "Assets/Sprites/objects/objects1.png",
                                                                                      "Assets/Sprites/objects/OBJECT_ICONS.png",
                                                                                      "Assets/Sprites/editor/tools.png" };
const std::string TextureManager::fontPaths[TextureManager::TOTAL_FONTS] = { "Assets/textures/Text/font1.png"};

TileMap TextureManager::tileMap;

void TextureManager::initalizeTextureManager()
{
    miscellaneous.push_back(LTexture());
    miscellaneous[0].loadFromFile("Assets/textures/Miscellaneous/delete.png", GraphicsEngine::getActiveRenderer());


    background_layer_textures.resize(TOTAL_BACKGROUND_TEXTURES);

    for (int i = 0; i < TOTAL_BACKGROUND_TEXTURES; i++) {
        background_layer_textures.push_back(std::vector<LTexture>());
        //Right now a background layer is limited to 5 parallax layers because of this for loop
        //This loop needs to be replaced by something more clever
        for (int j = 0; j < 3; j++) {
            background_layer_textures[i].push_back(LTexture());
        }
    }
    background_layer_textures[DEFAULT_BACKGROUND_LAYER][0].loadFromFile("Assets/textures/Backgrounds/purple background2.png", GraphicsEngine::getActiveRenderer());
    background_layer_textures[DEFAULT_BACKGROUND_LAYER][1].loadFromFile("Assets/textures/Backgrounds/plx0.png", GraphicsEngine::getActiveRenderer());
    background_layer_textures[DEFAULT_BACKGROUND_LAYER][2].loadFromFile("Assets/textures/Backgrounds/plx1.png", GraphicsEngine::getActiveRenderer());

    for (int i = 0; i < TOTAL_SPRITE_SHEETS; i++) {
        spriteSheets.push_back(LTexture());
    }
    for (int i = 0; i < TOTAL_SPRITE_SHEETS; i++) {
        spriteSheets[i].loadFromFile(sheetPaths[i], GraphicsEngine::getActiveRenderer());
    }
    for (int i = 0; i < TOTAL_FONTS; i++) {
        fontTextures.push_back(LTexture());
    }
    for (int i = 0; i < TOTAL_FONTS; i++) {
        fontTextures[i].loadFromFile(fontPaths[i], GraphicsEngine::getActiveRenderer());
    }
}

void TextureManager::loadTileSet(TILEMAPS map)
{
    if (map >= TOTAL_MAPS) {
        return;
    }
    tileMap.loadFromFile(mapPaths[map], colliderPaths[map]);
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
    for (int i = 0; i < TOTAL_SPRITE_SHEETS; i++) {
        spriteSheets[i].free();
    }

    for (int i = 0; i < TOTAL_BACKGROUND_TEXTURES; i++) {
        for each (LTexture tex in background_layer_textures[i]) {
            tex.free();
        }
    }
}

