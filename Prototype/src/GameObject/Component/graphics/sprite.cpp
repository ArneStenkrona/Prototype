#include "sprite.h"
#include "System/graphics/textureManager.h"

Sprite::Sprite(GameObject * _object) : Component(_object), startIndex(-1), endIndex(-1), frameFactor(3), frameFactorCounter(0)
{
    texture = &TextureManager::tile_textures[TextureManager::DEFAULT_TILE_TEXTURE];
}

void Sprite::update()
{
    if (!(startIndex == endIndex || startIndex == -1 || endIndex == -1)) {
        if (frameFactorCounter >= frameFactor) {
            frameFactorCounter = 0;
            tileIndex++;
            if (tileIndex > endIndex) tileIndex = startIndex;
        }
        frameFactorCounter++;
    }
}

int Sprite::getWidth()
{
    return texture->getWidth();
}

int Sprite::getHeight()
{
    return texture->getHeight();
}

void Sprite::setTileIndex(int i)
{
    tileIndex = i;
}

int Sprite::getTileIndex()
{
    return tileIndex;
}

void Sprite::setAnimationIndicies(int startInd, int endInd)
{
    startIndex = startInd;
    endIndex = endInd;
}

