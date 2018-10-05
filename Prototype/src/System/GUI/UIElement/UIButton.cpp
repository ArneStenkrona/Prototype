#include "UIButton.h"
#include "System\IO\inputManager.h"

UIButton::UIButton(EditorWindow* _owner,int _positionX, int _positionY, int _width, int _height,
                   int _layer, std::string _text)
    :UIElement(_positionX, _positionY, _width, _height, _layer, true),
     text(_text), owner(_owner)
{
}

void UIButton::notify()
{
    owner->notify(this);
}

void UIButton::onMouseOver()
{
    mouseOver = true;
    if (getKey(MOUSE_LEFT)) {
        holdClick = true;
    }
    if (getKeyUp(MOUSE_LEFT)) {
        notify();
    }
}

void UIButton::update()
{
    mouseOver = false;
    holdClick = false;
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

    UIElement::drawSquare(width, height, renderColor);
    UIElement::drawSquare(width, height, {60, 60, 60, 255}, OUTLINE_SQUARE);

    UIElement::renderText(text, { 0,0,0,0 }, ALIGN_CENTER, 1, 1);
    UIElement::renderText(text, { 255,255,255,255 }, ALIGN_CENTER);
}
