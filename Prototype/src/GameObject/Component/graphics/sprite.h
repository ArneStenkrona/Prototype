#pragma once
#include <stdio.h>
#include <string>
#include "../component.h"
#include "System/graphics/lTexture.h"

class Sprite : public Component {
public:
    Sprite(GameObject * _object);

    void update();

    //Gets image dimensions
    inline int getWidth() const { return texture->getHeight(); }
    inline int getHeight() const { return texture->getWidth(); };

    LTexture *texture;

    void setTileIndex(int i);
    inline int getTileIndex() const { return tileIndex; }

    //Sets height and width factors
    void setWidthHeight(int width, int height);

    void renderSprite(int x, int y);
    void renderSprite(int x, int y, double rotation, Point pivot);

    void setRenderOffset(int x, int y);

    void setMirror(bool horizontal, bool vertical);

    void rayHit(RayCastHit* hit);

private:
    //How many tiles the sprite occupies;
    //Example: widthFactor = 2 and heightFactor = 3 is a sprite that takes up 2 tiles in width and 3 tiles in height
    int widthFactor, heightFactor;

    //Index on the tile sheet of the tile
    //Set to -1 if no tileIndex (whole texture will be rendered)
    int tileIndex;

    //The coordinates for the render offset
    int renderOffsetX;
    int renderOffsetY;

    //mirrrors the sprite
    bool mirrorH;
    bool mirrorV;

    friend class Animator;
};