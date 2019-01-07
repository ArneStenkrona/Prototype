#pragma once
#include "..\..\UIElement.h"
#include "..\..\UIEvent\UIActionListener.h"

class UIPanel;
//Components are GUI objects that can be attached to a panel.
class UIComponent : public UIElement {
public:
    UIComponent(int _posx, int _posy, unsigned int _width, unsigned int _height, int _layer, UIActionListener* _listener = nullptr);
    virtual ~UIComponent();

protected:
    void onMouseOver();

    UIActionListener* getListener() const { return listener; }

    //Generates and sends an event to owner
    //Event does not survive the sendEvent function call
    virtual void sendEvent(std::string message = "");
private:
    //Panel that component is attached to. Can be nullptr.
    UIPanel* panel;
    //Listener that listens to this component. Can be nullptr.
    UIActionListener* listener;

    friend class UIPanel;
};