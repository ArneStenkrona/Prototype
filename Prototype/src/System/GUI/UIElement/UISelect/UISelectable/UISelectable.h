#pragma once
#include "../../UIElement.h"
#include "System\graphics\color.h"

class UISelector;
//Class for selectable UI elements
//An index is retrievable, which can be used to determine what object is selected
class UISelectable : public UIElement {
public:
    UISelectable(UISelector* _selector, int _posX, int _posY, unsigned int _width, unsigned int _height, unsigned int _layer,
        int _index);
    ~UISelectable();

    // returns index of the placable item contained
    inline int getIndex() const { return index; }
    
protected:    
    // index of the placable item contained
    const int index;

    UISelector* selector;

    //called when selected
    virtual void select();

    void onSelect();
    void onDeselect();

    //called if mouse is over
    void onMouseOver();

    void onMouseLeft();

    void render();
private:

    //unconditional update
    void update();

    friend class UISelector;
};