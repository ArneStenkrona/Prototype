#pragma once
#include "UISelectableTile.h"
#include "UISelector.h"
#include <set>

class UITileSelector : public UISelector {
public:
    UITileSelector(int _posx, int _posy, int _layer,
                    unsigned int _columns, unsigned int _rows,
                    Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_YELLOW);

    //Creates and returns a tile based on selected
    Tile* getTile() const;
    //Renders the selected at position (x, y)
    void renderSelected(int x, int y, Color color = COLOR_WHITE);



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
    void clearHoverIndices();

    //Returns true if index is within selected area as defined by offset and tileDim
    bool withinSelection(int idx);
    //Returns true if index is within hovered area as defined by offset and tileDim
    bool withinHover(int idx);

    //Sets c to border color for the UISelectable with given index
    //Sets b to bordertype for the given index as defined below
    // 0: full, 
    // 1: topleft, 2: topright, 3: bottomright, 4 bottomleft 
    // 5: top, 6: right, 7: bottom, 8: left 
    //Returns true if there should be a border for the given index
    bool getBorderColorAndType(int index, Color &c, int &b);

    friend class UISelectableTile;
};