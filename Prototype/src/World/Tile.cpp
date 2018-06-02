#include "Tile.h"
#include "GameObject\Component\geometry\position.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "GameObject\Component\graphics\renderer.h"

Tile::Tile(int _tileIndex): tileIndex(_tileIndex)
{
    int colliderCol = tileIndex % 16;
    int colliderRow = tileIndex / 16;
    //collider = (TextureManager::tileMap.colliderMatrix[0][0] != NULL);
    //if (collider) {
        polygon = TextureManager::tileMap.colliderMatrix[colliderCol][colliderRow];
        //collider = true;
    //} else printf("NULL COLLIDER \n");
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
    obj->addComponent<Renderer>()->setTileIndex(tileIndex);
    if (collider) {
        obj->addComponent<PolygonCollider>()->setPolygon(polygon);
    }
    obj->addComponent<Sprite>()->texture = &TextureManager::tileMap.texture;
    return obj;
}

void Tile::renderTile(int x, int y)
{
    TextureManager::tileMap.texture.renderTile(x, y, tileIndex);
}
