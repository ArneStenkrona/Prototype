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

    //sets startIndex and endIndex
    void setAnimationIndicies(int start, int end);

    void setFrameFactor(int i);
    inline int getFrameFactor() const { return frameFactor; }

    void renderSprite(int x, int y);
    void renderSprite(int x, int y, double rotation, Point pivot);

    void setRenderOffset(int x, int y);

    void setMirror(bool horizontal, bool vertical);

    void rayHit(RayCastHit* hit);

private:
    //How many tiles the sprite occupies;
    //Example: widthFactor = 2 and heightFactor = 3 is a sprite that takes up 2 tiles in width and 3 tiles in height
    int widthFactor, heightFactor;

    //boundaries of the animation (both inclusive)
    //startIndex == endIndex or negative values for either implies no animation;
    int startIndex, endIndex;

    //Index on the tile sheet of the tile
    //Set to -1 if no tileIndex (whole texture will be rendered)
    int tileIndex;

    //determines how many in-game frames a sprite frame should be displayed
    //Example: a frameFactor of 3 and an in-game fps of 60 displays an animation at 20 fps
    int frameFactor;
    //Incremented every in-game frame.
    //If equal to frameFactor, set to 0 and increment tileIndex
    int frameFactorCounter;

    //The coordinates for the render offset
    int renderOffsetX;
    int renderOffsetY;

    //mirrrors the sprite
    bool mirrorH;
    bool mirrorV;
};