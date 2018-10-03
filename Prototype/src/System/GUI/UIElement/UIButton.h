#pragma once
#include "UIElement.h"
#include <string>
#include "System\GUI\Window\EditorWindow.h"

class UIButton : public UIElement {
public:
    UIButton(EditorWindow* _owner, int _positionX, int _positionY, int _width, int _height,
             int _layer, std::string _text);
 
protected:
    const std::string text;
    
    //notifies owner
    virtual void notify();

private:
    void onMouseOver();
    void update();
    void render();

    //mouse is over
    bool mouseOver;
    //Click is held while mouse over
    bool holdClick;

    EditorWindow* owner;
};