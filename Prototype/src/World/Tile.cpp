#include "Tile.h"
#include "GameObject\Component\geometry\position.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "GameObject\Component\graphics\spriteRenderer.h"

Tile::Tile(int _tileIndex) : Tile(_tileIndex, {}, 0)
{
}

Tile::Tile(int _tileIndex, int _rotation): Tile(_tileIndex, {}, _rotation)
{
    int colliderCol = tileIndex % 16;
    int colliderRow = tileIndex / 16;

    polygon = TextureManager::tileMap.colliderMatrix[colliderCol][colliderRow];
}

Tile::Tile(int _tileIndex, optional<Polyshape> _polygon): Tile(_tileIndex, _polygon, 0)
{
}

Tile::Tile(int _tileIndex, std::optional<Polyshape> _polygon, int _rotation)
    : tileIndex(_tileIndex), polygon(_polygon), rotation(_rotation)
{
}

Tile::~Tile()
{
}

bool Tile::hasCollider()
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

GameObject* Tile::gameObjectFromTile(int x, int y)
{
    GameObject *obj = new GameObject();
    obj->addComponent<Position>()->position = Point(x * 32, y * 32);
    obj->addComponent<SpriteRenderer>();
    obj->addComponent<Sprite>()->texture = &TextureManager::tileMap.texture;
    obj->getComponent<Sprite>()->setTileIndex(tileIndex);
    if (rotation) {
        obj->addComponent<Rotation>()->rotation = (rotation * 90);
        obj->getComponent<Rotation>()->pivot = Point(16,16);
    }

    if (hasCollider()) {
        obj->addComponent<PolygonCollider>()->setPolygon(polygon.value());
    }

    return obj;
}

void Tile::renderTile(int x, int y)
{
    if (rotation)
    TextureManager::tileMap.texture.renderTile(x, y, tileIndex,
                                               1,1, false, false,
                                               rotation * 90, 16, 16);
    else 
        TextureManager::tileMap.texture.renderTile(x, y, tileIndex);
}
