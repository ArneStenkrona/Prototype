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
    ~UISelectable();

    inline int getIndex() const { return index; }
    inline void setIndex(int _index) { index = _index; }
    
protected:    
    int index;

    Color currentColor;
    Color selectedColor;
    Color hoverColor;

    UISelector* selector;

    //Renders before border
    virtual void derivedRender();
    //updates before regular update()
    virtual void derivedUpdate();
    //called when selected
    virtual void select();
    //called when unselected
    //virtual void unselect();

    void onSelect();
    void onDeselect();

    //called if mouse is over
    void onMouseOver();
private:

    void render();
    //unconditional update
    void update();



    friend class UISelector;
};