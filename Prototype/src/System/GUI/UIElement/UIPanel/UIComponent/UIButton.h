#pragma once
#include "UIButtonBase.h"
#include <string>

class UIButton : public UIButtonBase {
public:
    //Creates an instance of UIButton with listener _listener.
    //The listener is destroyed when UIButton is destroyed
    UIButton(UIActionListener* _listener, int _positionX, int _positionY, int _width, int _height,
             int _layer, std::string _text);
    virtual ~UIButton();
 
protected:

private:
    void render();
};