#pragma once
#include "UIElement.h"

class UIBorder : public UIElement {
public:
    UIBorder(int _posX, int _posY,
             int _border_width, int _border_height, int _layer, Color _color = COLOR_BLACK);
private:
    Color color;
    void render();
};