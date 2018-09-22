#include "UISelectCollider.h"
#include "UIColliderSelector.h"
#include "System\IO\inputManager.h"
#include "math\rectangle.h"
#include "math\triangle.h"
std::vector<Polyshape> UISelectCollider::polygons = { Rectangular(Point(0, 0), 32, 32),
                                                      Triangle(Point(0, 0), Point(32, 32), Point(0, 32)),
                                                      Triangle(Point(32, 0), Point(32, 32), Point(0, 32)),
                                                      Triangle(Point(0, 0), Point(32, 0), Point(0, 32)),
                                                      Triangle(Point(32, 0), Point(32, 32), Point(0, 0)) };

UISelectCollider::UISelectCollider(UIColliderSelector * _selector, int _posx, int _posy, unsigned int _layer, int _polygonIndex)
                : UIElement(_posx, _posy, 32, 32, _layer, true), polygonIndex(_polygonIndex),
                  selector(_selector)
{
}

void UISelectCollider::render()
{
    UIElement::drawSolidSquare(positionX, positionY, { 0, 0, 0, 255 });
    if (polygons.size() > polygonIndex) polygons[polygonIndex].renderPolygon(positionX, positionY);
    UIElement::drawOutlineSquare(positionX, positionY, { r, g, b, a });
}

void UISelectCollider::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT)) {
        selector->setIndex(polygonIndex);
        r = 0x00;
        g = 0xff;
        b = 0x00;
        a = 0xff;
    }
    else {
        r = 0x00;
        g = 0xff;
        b = 0xff;
        a = 0xff;
    }
}

void UISelectCollider::update()
{
    if (selector->getSelectedIndex() == polygonIndex) {
        r = 0x80;
        g = 0x00;
        b = 0x80;
        a = 0xff;
    }
    else {
        r = 0x00;
        g = 0x00;
        b = 0x00;
        a = 0x00;
    }
}
