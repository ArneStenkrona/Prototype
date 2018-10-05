#include "UISelectableCollider.h"
#include "math\polygon.h"
#include "World\Tile.h"

UISelectableCollider::UISelectableCollider(UISelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                           int _index, Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index, _selectedColor, _hoverColor)
{
}

void UISelectableCollider::derivedRender()
{
    UIElement::drawSquare(width, height, { 0, 0, 0, 255 });
    if (Polyshape::basicPolygons.size() > index) Polyshape::basicPolygons[index].renderPolygon(positionX, positionY);
}

void UISelectableCollider::derivedUpdate()
{
}
