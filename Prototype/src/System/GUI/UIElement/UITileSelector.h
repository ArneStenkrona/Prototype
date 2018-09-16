#pragma once
#include "UISelectTile.h"
#include <vector>

class UITileSelector : public UIElement {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows);
    ~UITileSelector();

    inline unsigned int getSelectedIndex() const { return selectedTileIndex; }
    inline unsigned int getRotation() const { return rotation; }
    inline void getFlip(bool &_flipH, bool &_flipV) { _flipH = flipH; _flipV = flipV; }
    void setIndex(unsigned int _index) { selectedTileIndex = _index; rotation = 0; }
    void moveIndices(int dx, int dy);
private:
    std::vector<std::vector<UISelectTile*>> tiles;
    //selected tileIndex
    int selectedTileIndex;
    //offset for indicies
    int indX, indY;
    unsigned int columns, rows;

    void update();

    int rotation;
    bool flipH, flipV;
};