#include "UIMovable.h"
#include "System\IO\inputManager.h"

UIMovable::UIMovable(int _positionX, int _positionY, int _width, int _height, int _layer)
    :UIPanel(_positionX, _positionY, _width, _height, _layer), drag(false)
{
}

void UIMovable::derivedUpdate()
{
}

void UIMovable::onMouseOver()
{
    if (getKey(MOUSE_LEFT)) {
        getMouseWorldCoordinates(lastMouseX, lastMouseY);
        drag = true;
    }
}

void UIMovable::update()
{
    UIPanel::update();

    if (drag) {
        int mx, my = 0;
        getMouseWorldCoordinates(mx, my);
        positionX += mx - lastMouseX;
        positionY += my - lastMouseY;

        for (UIElement*  e : attached) {
            e->positionX += mx - lastMouseX;
            e->positionY += my - lastMouseY;
        }
    }
    getMouseWorldCoordinates(lastMouseX, lastMouseY);
    drag = false;
    derivedUpdate();
}

void UIMovable::onSelect()
{
    moveToFrontOffLayer(0);
    for (UIElement* e : attached) {
        e->moveToFrontOffLayer(0);
    }
}
