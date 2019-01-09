#pragma once
#include "UIElement.h"

class UIGridEditor;
class UIGridTile : public UIElement {
public:
    UIGridTile(UIGridEditor* _selector, int _layer, 
                        unsigned int indX, unsigned int indY);

    bool selected;

    void updatePosition();

private:
    unsigned int indX, indY;
    //Is the tile going to be unseen ingame due to room padding?
    bool padded;

    void render();
    //called if mouse enters
    virtual void onMouseEnter();
    //called if mouse is over
    void onMouseOver();
    //called if mouse leaves
    void onMouseExit();
    //unconditional update
    void update();
    void onSelect();
    void onDeselect();

    UIGridEditor* selector;
};