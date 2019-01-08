#include "Tile.h"
#include "GameObject\Component\geometry\position.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "GameObject\Component\graphics\spriteRenderer.h"
#include "GameObject\Component\environment\material.h"
#include "World\objects\object.h"
#include <iostream>

const size_t Tile::TILE_SIZE = 16;
//This is assuming a tilesheet is 512x512 pixels
const size_t Tile::TILES_PER_ROW = 512 / Tile::TILE_SIZE;
const size_t Tile::TILES_PER_COLUMN = 512 / Tile::TILE_SIZE;
const unsigned int Tile::tileToPixel[16] = { 0 * Tile::TILE_SIZE,
                                             1 * Tile::TILE_SIZE,
                                             2 * Tile::TILE_SIZE,
                                             3 * Tile::TILE_SIZE,
                                             4 * Tile::TILE_SIZE,
                                             5 * Tile::TILE_SIZE,
                                             6 * Tile::TILE_SIZE,
                                             7 * Tile::TILE_SIZE,
                                             8 * Tile::TILE_SIZE,
                                             9 * Tile::TILE_SIZE,
                                             10 * Tile::TILE_SIZE,
                                             11 * Tile::TILE_SIZE,
                                             12 * Tile::TILE_SIZE,
                                             13 * Tile::TILE_SIZE,
                                             14 * Tile::TILE_SIZE,
                                             15 * Tile::TILE_SIZE };

Tile::Tile(int _tileIndex, int _rotation, bool _flipH, bool _flipV, 
           std::optional<Polyshape> _polygon, int _objectIndex, std::vector<std::string> _objectparameters)
    : tileIndex(_tileIndex), polygon(_polygon), rotation(_rotation),
    flipH(_flipH), flipV(_flipV), objectIndex(_objectIndex), objectParameters(_objectparameters)
{
}

Tile::~Tile()
{
}

bool Tile::hasCollider() const
{
    return polygon.has_value();
}

Polyshape * Tile::getPolygon()
{
    if (polygon.has_value())
        return &polygon.value();
    else
        return NULL;
}

int Tile::getIndex()
{
    return tileIndex;
}

void Tile::setObject(int index, std::vector<std::string> parameters)
{
    objectIndex = index; 
    objectParameters = parameters;
}

GameObject* Tile::gameObjectFromTile(int x, int y) const
{
    GameObject *obj = new GameObject();
    obj->addComponent<Position>()->position = Point(x * TILE_SIZE, y * TILE_SIZE);
    if (tileIndex >= 0) {
        obj->addComponent<SpriteRenderer>();
        obj->addComponent<Sprite>()->texture = &TextureManager::tileMap.texture;
        obj->getComponent<Sprite>()->setTileIndex(tileIndex);
        obj->getComponent<Sprite>()->setMirror(flipH, flipV);
            if (rotation) {
                obj->addComponent<Rotation>()->rotation = (rotation * 90);
                obj->getComponent<Rotation>()->pivot = Point(TILE_SIZE / 2, TILE_SIZE / 2);
            }
    }

    if (hasCollider()) {
        obj->addComponent<PolygonCollider>()->setPolygon(polygon.value());
        obj->addComponent<Material>()->soundMap = { {"lsr", SoundManager::THUD_SOUND} };
    }

    return obj;
}

GameObject* Tile::instantiateObject(int x, int y) const
{
    if (objectIndex >= 0) {
        GameObject* g = Object::objects[objectIndex].instantiate(objectParameters);
        if (g->hasComponent<Position>())
            g->getComponent<Position>()->position = Point(x * Tile::TILE_SIZE, y * Tile::TILE_SIZE);
        return g;
    }
    else
        return NULL;
}

void Tile::renderTile(int x, int y)
{
    //Render actual tile
    if (rotation || flipH || flipV)
    TextureManager::tileMap.texture.renderTile(x, y, tileIndex,
                                               1,1, flipH, flipV,
                                               rotation * 90, TILE_SIZE / 2, TILE_SIZE / 2);
    else 
        TextureManager::tileMap.texture.renderTile(x, y, tileIndex);
    if (polygon.has_value())
        polygon.value().renderPolygon(x, y);

    //Render object
    if (objectIndex >= 0)
        TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(x, y, objectIndex,
                                                                              1, 1, false, false,
                                                                              0, TILE_SIZE / 2, TILE_SIZE / 2);
}
