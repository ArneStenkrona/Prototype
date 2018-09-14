#pragma once
#include "UIElement.h"
#include "System\graphics\textureManager.h"

class UITileSelector;
class UISelectTile : public UIElement {
public:
    UISelectTile(UITileSelector* _selector, int _posx, int _posy,
           unsigned int _layer, int _tileIndex);
    
    void setTileIndex(int index) { tileIndex = index; }

    bool selected;
private:
    int tileIndex;

    //border colors
    unsigned char r, g, b, a;

    void render();
    //called if mouse is over
    void onMouseOver();
    //unconditional update
    void update();

    UITileSelector* selector;
    int rotation;
};