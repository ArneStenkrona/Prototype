#pragma once
#include "UIElement.h"

class UIPanel;
//Components are GUI objects that can be attached to a panel
class UIComponent : public UIElement {
public:
    UIComponent(int _posx, int _posy, int _width, int _height, int _layer);
protected:
    void onMouseOver();
private:
    //Panel that component is attached to. Can be NULL
    UIPanel* panel;


    friend class UIPanel;
};