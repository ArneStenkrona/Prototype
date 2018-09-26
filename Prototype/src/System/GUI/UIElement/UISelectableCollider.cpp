#include "UISelectableCollider.h"
#include "math\polygon.h"

UISelectableCollider::UISelectableCollider(UISelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                           int _index, Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index, _selectedColor, _hoverColor)
{
}

void UISelectableCollider::derivedRender()
{
    UIElement::drawSolidSquare({ 0, 0, 0, 255 });
    if (Polyshape::basicPolygons.size() > index) Polyshape::basicPolygons[index].renderPolygon(positionX, positionY);
}

void UISelectableCollider::derivedUpdate()
{
}
