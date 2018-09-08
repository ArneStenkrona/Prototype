#include "Tile.h"
#include "GameObject\Component\geometry\position.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "GameObject\Component\graphics\spriteRenderer.h"

Tile::Tile(int _tileIndex): tileIndex(_tileIndex)
{
    int colliderCol = tileIndex % 16;
    int colliderRow = tileIndex / 16;
    
    polygon = TextureManager::tileMap.colliderMatrix[colliderCol][colliderRow];
}

Tile::Tile(int _tileIndex, optional<Polyshape> _polygon): tileIndex(_tileIndex), polygon(_polygon)
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
    obj->addComponent<SpriteRenderer>();// ->setTileIndex(tileIndex);
    obj->addComponent<Sprite>()->texture = &TextureManager::tileMap.texture;
    obj->getComponent<Sprite>()->setTileIndex(tileIndex);
    if (hasCollider()) {
        obj->addComponent<PolygonCollider>()->setPolygon(polygon.value());
    }
    return obj;
}

void Tile::renderTile(int x, int y)
{
    TextureManager::tileMap.texture.renderTile(x, y, tileIndex);
}
