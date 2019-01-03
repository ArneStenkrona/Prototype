#pragma once
#include "UIComponent.h"
#include <string>
#include "UIActionListener.h"

class UIButton : public UIComponent {
public:
    //Creates an instance of UIButton with listener _listener.
    //The listener is destroyed when UIButton is destroyed
    UIButton(UIActionListener* _listener, int _positionX, int _positionY, int _width, int _height,
             int _layer, std::string _text);
    virtual ~UIButton();
 
protected:
    const std::string text;
    
    //Generates and sends an event to owner
    //Event does not survive the sendEvent function call
    virtual void sendEvent();

private:
    void onMouseOver();
    void update();
    void render();

    //mouse is over
    bool mouseOver;
    //User has initiated click on button
    bool holdClick;

    UIActionListener* listener;
};