#pragma once
#include "UIElement.h"

class UIGridSelector;
class UIGridTile : public UIElement {
public:
    UIGridTile(UIGridSelector* _selector, int _layer, 
                        unsigned int indX, unsigned int indY);

    bool selected;
private:
    unsigned int indX, indY;

    //border colors
    unsigned char r, g, b, a;

    void render();
    //called if mouse is over
    void onMouseOver();
    //called if mouse leaves
    void onMouseLeft();
    //unconditional update
    void update();
    void onSelect();
    void onDeselect();

    UIGridSelector* selector;
};