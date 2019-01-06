#include "UIButton.h"
#include "System\IO\inputManager.h"
#include "..\..\UIEvent\UIEvent.h"

UIButton::UIButton(UIActionListener* _listener, int _positionX, int _positionY, int _width, int _height,
                   int _layer, std::string _text)
    :UIButtonBase(_listener, _positionX, _positionY, _width, _height, _layer, _text)
{
}

UIButton::~UIButton()
{
    delete listener;
    listener = nullptr;
}

void UIButton::render()
{
    Color renderColor;
    if (getHoldClick())
        renderColor = { 66, 134, 244, 255 };
    else if (getMouseOver())
        renderColor = { 120, 120, 120, 255 };
    else
        renderColor = { 80, 80, 80, 255 };

    Color outlineColor;
    if (isSelected())
        outlineColor = { 66, 134, 244, 255 };
    else
        outlineColor = { 60, 60, 60, 255 };

    UIElement::drawSquare(width, height, renderColor, SOLID);
    UIElement::drawSquare(width, height, outlineColor, OUTLINE);

    UIElement::renderTextBackdrop(text, { 255,255,255,255 }, ALIGN_CENTER);
}
