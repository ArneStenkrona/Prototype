#include "UIRadioButton.h"

UIRadioButton::UIRadioButton(UIActionListener * _listener, int _positionX, int _positionY, unsigned int _diameter, int _layer, std::string _text)
    :UIButtonBase(_listener, _positionX, _positionY, _diameter, _diameter, _layer, _text)
{
}

UIRadioButton::~UIRadioButton()
{
}

void UIRadioButton::addToGroup(RadioButtonGroup * /* _group*/)
{
}

void UIRadioButton::render()
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

    UIElement::drawCircle(width, renderColor, SOLID);
    UIElement::drawCircle(width, outlineColor, OUTLINE);
}
