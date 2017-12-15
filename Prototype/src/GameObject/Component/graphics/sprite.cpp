#include "sprite.h"
#include "System/graphics/textureManager.h"

Sprite::Sprite(GameObject * _object) : Component(_object)
{
    texture = &TextureManager::tile_textures[TextureManager::DEFAULT_TILE_TEXTURE];
}

int Sprite::getWidth()
{
    return texture->getWidth();
}

int Sprite::getHeight()
{
    return texture->getHeight();
}

