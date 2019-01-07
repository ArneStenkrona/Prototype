#pragma once
#include "UIComponent.h"
#include <string>
#include "..\..\UIEvent\UIActionListener.h"

class UIButtonBase : public UIComponent {
public:
    //Creates an instance of UIButton with listener _listener.
    //The listener is destroyed when UIButton is destroyed
    UIButtonBase(UIActionListener* _listener, int _positionX, int _positionY, unsigned  int _width, unsigned int _height,
        int _layer, std::string _text);
    virtual ~UIButtonBase();

    inline bool getMouseOver() const { return mouseOver; }
    inline bool getHoldClick()  const { return holdClick; }

protected:
    const std::string text;


private:
    //mouse is over
    bool mouseOver;
    //User has initiated click on button
    bool holdClick;
    //Listener
    UIActionListener* listener;

    //Inherited members from UIElement
    virtual void onMouseOver();
    virtual void update();
    virtual void render() = 0;
};