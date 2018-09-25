#include "sprite.h"
#include "System/graphics/textureManager.h"

Sprite::Sprite(GameObject * _object) : Component(_object), startIndex(-1), endIndex(-1),
frameFactor(3), frameFactorCounter(0), widthFactor(1), heightFactor(1),
renderOffsetX(0), renderOffsetY(0), mirrorH(false), mirrorV(false)
{
    texture = &TextureManager::miscellaneous[0];
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

void Sprite::setTileIndex(int i)
{
    tileIndex = i;
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

void Sprite::setFrameFactor(int i)
{
    frameFactor = i;
}

void Sprite::renderSprite(int x, int y)
{
    renderSprite(x, y, 0, Point(0,0));

}

void Sprite::renderSprite(int x, int y, double rotation, Point pivot)
{
    if (tileIndex == -1)
        texture->render((int)(x + 0.5) + renderOffsetX, (int)(y + 0.5) + renderOffsetY);
    else
        texture->renderTile((int)(x + 0.5) + renderOffsetX, (int)(y + 0.5) + renderOffsetY, tileIndex, widthFactor, heightFactor, mirrorH, mirrorV, rotation, pivot.x, pivot.y);
}

void Sprite::setRenderOffset(int x, int y)
{
    renderOffsetX = x;
    renderOffsetY = y;
}

void Sprite::setMirror(bool horizontal, bool vertical)
{
    mirrorH = horizontal;
    mirrorV = vertical;
}

void Sprite::rayHit(RayCastHit * hit)
{ 

}

