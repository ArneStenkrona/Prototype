#pragma once
#include "UIElement.h"
#include "UISelectable.h"
#include "World\Tile.h"

class UISelectableTile : public UISelectable {
public:
    UISelectableTile(UISelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index, Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);
private:
    void derivedRender();
    void select();
    void unselect();
    int rotation;
    bool flipH, flipV;
};