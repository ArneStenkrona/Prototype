#pragma once
#include "UIElement.h"
#include <string>

class UIButton : public UIElement {
public:
    UIButton(int _positionX, int _positionY, int _width, int _height,
             int _layer, std::string _text);
 
protected:
    const std::string text;
    
    //action to be taken when button is pressed
    virtual void action();

private:
    void onMouseOver();
    void update();
    void render();

    //mouse is over
    bool mouseOver;
    //Click is held while mouse over
    bool holdClick;
};