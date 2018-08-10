#include "sprite.h"
#include "System/graphics/textureManager.h"

Sprite::Sprite(GameObject * _object) : Component(_object), startIndex(-1), endIndex(-1), 
frameFactor(3), frameFactorCounter(0), widthFactor(1), heightFactor(1), renderOffsetX(0), renderOffsetY(0)
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

void Sprite::setWidthHeight(int width, int height)
{
    if (width <= 16 && width > 0) widthFactor = width;
    if (height <= 16 && height > 0) heightFactor = height;

}

void Sprite::setAnimationIndicies(int startInd, int endInd)
{
    startIndex = startInd;
    endIndex = endInd;
    tileIndex = startIndex;
}

void Sprite::renderSprite(int x, int y)
{
    if (tileIndex == -1) 
        texture->render((int)(x + 0.5) + renderOffsetX, (int)(y + 0.5) + renderOffsetY);
    else
        texture->renderTile((int)(x + 0.5) + renderOffsetX, (int)(y + 0.5) + renderOffsetY, tileIndex, widthFactor, heightFactor);

}

void Sprite::setRenderOffset(int x, int y)
{
    renderOffsetX = x;
    renderOffsetY = y;
}

