#include "UIButtonBase.h"
#include "System\IO\inputManager.h"
#include "UIEvent.h"

UIButtonBase::UIButtonBase(UIActionListener * _listener, int _positionX, int _positionY, 
                           int _width, int _height, int _layer, std::string _text)
    :UIComponent(_positionX, _positionY, _width, _height, _layer),
     text(_text), listener(_listener), holdClick(false)
{
}

UIButtonBase::~UIButtonBase()
{
    delete listener;
    listener = nullptr;
}

void UIButtonBase::sendEvent()
{
    UIEvent* e = new UIEvent();
    listener->actionPerformed(e);
    delete e;
}

void UIButtonBase::onMouseOver()
{
    UIComponent::onMouseOver();
    mouseOver = true;
    if (getKeyDown(MOUSE_LEFT)) {
        holdClick = true;
    }
    if (getKeyUp(MOUSE_LEFT) && isSelected()) {
        sendEvent();
    }
}

void UIButtonBase::update()
{
    mouseOver = false;
    if (!getKey(MOUSE_LEFT))
        holdClick = false;
    if (isSelected() && (getKey(INPUT_KEY_KP_ENTER) || getKey(INPUT_KEY_RETURN))) {
        holdClick = true;
    }
    if (isSelected() && (getKeyUp(INPUT_KEY_KP_ENTER) || getKeyUp(INPUT_KEY_RETURN))) {
        sendEvent();
    }
}
