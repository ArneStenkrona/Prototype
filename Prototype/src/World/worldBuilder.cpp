#include "worldBuilder.h"
#include "gameObject/Component/graphics/renderer.h"
#include "System/graphics/textureManager.h"
#include "gameObject/Component/geometry/polygonCollider.h"
#include <iostream>


GameObject *createTile(Tile tile)
{
    GameObject *obj = new GameObject();
    obj->addComponent<Position>()->position = Point(tile.x * 32, tile.y * 32);
    obj->addComponent<Renderer>();
    if (tile.hasCollider) {
        obj->addComponent<PolygonCollider>()->setPolygon(tile.polygon);
    }
    obj->addComponent<Sprite>()->texture = &TextureManager::tile_textures[tile.tileIndex];

    return obj;
}