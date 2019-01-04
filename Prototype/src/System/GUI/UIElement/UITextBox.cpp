#include "UITextBox.h"
#include "System\IO\inputManager.h"

UITextBox::UITextBox(int _positionX, int _positionY, int _length, int _layer)
    : UIComponent(_positionX, _positionY, _length, 16, _layer)
{
}

void UITextBox::render()
{
    UIElement::drawSquare(width, height, { 50,50,50,255 }, SOLID, ALIGN_CENTER);
    //Render only part of string that fits within the box
    int start = input.length() - (width - 10) / 4;
    start = start < 0 ? 0 : start;
    std::string rText = input.substr(start, input.length());
    UIElement::renderText(rText, { 255,255,255,255 }, ALIGN_LEFT, 5);

    if (isSelected())
        UIElement::drawSquare(width, height, { 66, 134, 244, 255 }, OUTLINE);
}

void UITextBox::update()
{
    if (isSelected())
        modifyStringFromInput(input);
}
