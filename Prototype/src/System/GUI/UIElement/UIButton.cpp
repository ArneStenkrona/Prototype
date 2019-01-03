#include "UIButton.h"
#include "System\IO\inputManager.h"
#include "UIEvent.h"
#include <iostream>

UIButton::UIButton(UIActionListener* _listener, int _positionX, int _positionY, int _width, int _height,
                   int _layer, std::string _text)
    :UIComponent(_positionX, _positionY, _width, _height, _layer),
     text(_text), listener(_listener), holdClick(false)
{
}

UIButton::~UIButton()
{
    delete listener;
    listener = nullptr;
}

void UIButton::sendEvent()
{
    UIEvent* e = new UIEvent();
    listener->actionPerformed(e);
    delete e;
}

void UIButton::onMouseOver()
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

void UIButton::update()
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

void UIButton::render()
{
    Color renderColor;
    if (holdClick)
        renderColor = { 66, 134, 244, 255 };
    else if (mouseOver)
        renderColor = { 120, 120, 120, 255 };
    else
        renderColor = { 80, 80, 80, 255 };

    Color outlineColor;
    if (isSelected())
        outlineColor = { 66, 134, 244, 255 };
    else
        outlineColor = { 60, 60, 60, 255 };

    UIElement::drawSquare(width, height, renderColor);
    UIElement::drawSquare(width, height, outlineColor, OUTLINE_SQUARE);

    UIElement::renderTextBackdrop(text, { 255,255,255,255 }, ALIGN_CENTER);
}
