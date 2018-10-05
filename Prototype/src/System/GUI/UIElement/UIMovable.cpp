#include "UIMovable.h"
#include "System\IO\inputManager.h"

UIMovable::UIMovable(int _positionX, int _positionY, int _width, int _height, int _layer)
    :UIElement(_positionX, _positionY, _width, _height, _layer, true), drag(false)
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
    if (drag) {
        int mx, my = 0;
        getMouseWorldCoordinates(mx, my);
        positionX += mx - lastMouseX;
        positionY += my - lastMouseY;
    }
    getMouseWorldCoordinates(lastMouseX, lastMouseY);
    drag = false;
    derivedUpdate();
}
