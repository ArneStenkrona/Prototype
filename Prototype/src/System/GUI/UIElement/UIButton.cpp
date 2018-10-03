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

    UIElement::drawSolidSquare(renderColor);
    UIElement::drawOutlineSquare({60, 60, 60, 255});

    UIElement::renderText(1,1, text, ALIGN_CENTER, { 0,0,0,0 });
    UIElement::renderText(0, 0, text, ALIGN_CENTER);
}
