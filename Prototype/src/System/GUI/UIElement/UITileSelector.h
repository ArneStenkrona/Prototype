#pragma once
#include "UISelectableTile.h"
#include "UISelector.h"
#include <vector>

class UITileSelector : public UISelector {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows,
                    Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);

    //Creates and returns a tile based on selected
    Tile* getTile() const;
private:
};