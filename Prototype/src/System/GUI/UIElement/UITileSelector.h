#pragma once
#include "UITile.h"
#include <vector>

class UITileSelector : public UIElement {
public:
    UITileSelector(int _posx, int _posy, unsigned int _layer,
                    unsigned int _columns, unsigned int _rows);
    ~UITileSelector();

    inline unsigned int getIndex() const { return tileMapIndex; }
    void setIndex(unsigned int _index) { tileMapIndex = _index; }
    void moveIndices(int dx, int dy);
private:
    std::vector<std::vector<UITile*>> tiles;
    //selected tileIndex
    unsigned int tileMapIndex;
    //offset for indicies
    unsigned int indX, indY;
    unsigned int columns, rows;
};