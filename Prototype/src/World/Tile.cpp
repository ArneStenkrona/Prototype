#include "Tile.h"
#include "GameObject\Component\geometry\position.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "GameObject\Component\graphics\renderer.h"

Tile::Tile(int _tileIndex): tileIndex(_tileIndex)
{
}

Tile::Tile(int _tileIndex, Polygon _polygon): tileIndex(_tileIndex), polygon(_polygon)
{
    collider = true;
}

Tile::~Tile()
{
}

bool Tile::hasCollider()
{
    return collider;
}

Polygon * Tile::getPolygon()
{
    return &polygon;
}

int Tile::getIndex()
{
    return tileIndex;
}

GameObject* Tile::gameObjectFromTile(int x, int y)
{
    GameObject *obj = new GameObject();
    obj->addComponent<Position>()->position = Point(x * 32, y * 32);
    obj->addComponent<Renderer>();
    if (collider) {
        obj->addComponent<PolygonCollider>()->setPolygon(polygon);
    }
    obj->addComponent<Sprite>()->texture = &TextureManager::tile_textures[tileIndex];

    return obj;
}
