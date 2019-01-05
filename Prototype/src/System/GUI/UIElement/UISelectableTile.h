#pragma once
#include "UIElement.h"
#include "UISelectable.h"
#include "World\Tile.h"

class UITileSelector;
class UISelectableTile : public UISelectable {
public:
    UISelectableTile(UITileSelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index);



private:
    void render();
    void onMouseExit();
};