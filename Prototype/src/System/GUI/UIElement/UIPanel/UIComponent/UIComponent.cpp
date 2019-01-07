#include "UIComponent.h"
#include "..\UIPanel\UIPanel.h"

UIComponent::UIComponent(int _posx, int _posy, unsigned int _width, unsigned int _height, 
                         int _layer, UIActionListener* _listener)
    :UIElement(_posx, _posy, _width, _height, _layer, true), listener(_listener)
{
}

UIComponent::~UIComponent()
{
    if (listener) {
        delete listener;
        listener = nullptr;
    }
}

void UIComponent::onMouseOver()
{
    if (panel != nullptr)
        panel->onMouseOver();
}

void UIComponent::sendEvent(std::string message)
{
    //Check if listener is present
    if (!listener) return;
    UIEvent* e = new UIEvent(message);
    listener->actionPerformed(e);
    delete e;
}
