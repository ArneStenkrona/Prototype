#pragma once
#include "UISelectTile.h"
#include <vector>

class UITileSelector : public UIElement {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows);
    ~UITileSelector();

    inline unsigned int getSelectedIndex() const { return selectedTileIndex; }
    void setIndex(unsigned int _index) { selectedTileIndex = _index; }
    void moveIndices(int dx, int dy);
private:
    std::vector<std::vector<UISelectTile*>> tiles;
    //selected tileIndex
    int selectedTileIndex;
    //offset for indicies
    int indX, indY;
    unsigned int columns, rows;
};