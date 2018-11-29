#pragma once
#include "UISelectableTile.h"
#include "UISelector.h"
#include <vector>
#include <tuple>

class UITileSelector : public UISelector {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows,
                    Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);

    //Creates and returns a tile based on selected
    Tile* getTile() const;
    //Renders the selected at position (x, y)
    void renderSelected(int x, int y, Color color = COLOR_WHITE);
protected:
private:
    //How many tiles should be selected
    unsigned int tileDim;

    const Color hoverColor;
    const Color selectedColor;

    void update();
    void render();
};