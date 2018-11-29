#pragma once
#include "UISelectableTile.h"
#include "UISelector.h"
#include <set>

class UITileSelector : public UISelector {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows,
                    Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);

    //Creates and returns a tile based on selected
    Tile* getTile() const;
    //Renders the selected at position (x, y)
    void renderSelected(int x, int y, Color color = COLOR_WHITE);

    //Returns true if index is within selected area as defined by offset and tileDim
    bool withinSelection(int idx);
    //Returns true if index is within hovered area as defined by offset and tileDim
    bool withinHover(int idx);


protected:
private:
    //How many tiles should be selected
    unsigned int tileDim;
    std::set<int> selectedIndices;
    std::set<int> hoverIndices;


    const Color hoverColor;
    const Color selectedColor;

    void update();
    void render();
    void setSelected(int i);
    void setHoverIndex(int i);
    void updateSelectedIndices();
    void updateHoverIndices();
};