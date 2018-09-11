#pragma once
#include "UIElement.h"
#include "System\graphics\textureManager.h"

class UITileSelector;
class UITile : public UIElement {
public:
    UITile(UITileSelector* _selector, int _posx, int _posy,
           unsigned int _layer, unsigned int _tileIndex);
    
    void setTileIndex(unsigned int index) { tileIndex = index; }

    bool selected;
private:
    unsigned int tileIndex;

    //border colors
    unsigned char r, g, b, a;

    virtual void render();
    //called if mouse is over
    virtual void onMouseOver();
    //unconditional update
    virtual void update();

    UITileSelector* selector;
};