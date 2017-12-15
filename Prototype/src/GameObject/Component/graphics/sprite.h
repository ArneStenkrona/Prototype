#pragma once
#include <stdio.h>
#include <string>
#include "../component.h"
#include "System/graphics/lTexture.h"
#include "System/graphics/global_graphical_variables.h"

class Sprite : public Component {
public:
    Sprite(GameObject * _object);


    //Gets image dimensions
    int getWidth();
    int getHeight();

    LTexture *texture;

};