#pragma once
#include "UIElement.h"
#include "System\graphics\color.h"

class UISelector;
//Class for selectable UI elements
//An index is retrievable, which can be used to determine what object is selected
class UISelectable : public UIElement {
public:
    UISelectable(UISelector* _selector, int _posX, int _posY, unsigned int _width, unsigned int _height, unsigned int _layer,
        int _index,  Color _selectedColor, Color _hoverColor);

    inline int getIndex() const { return index; }
    inline void setIndex(int _index) { index = _index; }
    
protected:    
    //Renders before border
    virtual void derivedRender();
    //updates before regular update()
    virtual void derivedUpdate();
    //called when selected
    virtual void select();
    //called when unselected
    virtual void unselect();
    int index;
    Color currentColor;
    Color selectedColor;
    Color hoverColor;

    UISelector* selector;
private:

    void render();
    //called if mouse is over
    void onMouseOver();
    //unconditional update
    void update();


    friend class UISelector;
};