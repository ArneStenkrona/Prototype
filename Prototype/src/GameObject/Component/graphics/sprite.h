#pragma once
#include <stdio.h>
#include <string>
#include "../component.h"
#include "System/graphics/lTexture.h"
#include "System/graphics/global_graphical_variables.h"

class Sprite : public Component {
public:
    Sprite(GameObject * _object);

    void update();

    //Gets image dimensions
    int getWidth();
    int getHeight();

    LTexture *texture;

    void setTileIndex(int i);
    int getTileIndex();

    //sets startIndex and endIndex
    void setAnimationIndicies(int start, int end);

private:
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
};