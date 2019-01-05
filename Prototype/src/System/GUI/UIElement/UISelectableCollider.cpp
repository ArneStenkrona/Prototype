#include "UISelectableCollider.h"
#include "UISelector.h"
#include "math\polygon.h"
#include "World\Tile.h"

UISelectableCollider::UISelectableCollider(UISelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                           int _index)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index)
{
}

void UISelectableCollider::render()
{
    UIElement::drawSquare(width, height, { 0, 0, 0, 255 });
    if ((signed)Polyshape::basicPolygons.size() > index + selector->getOffset()) 
        Polyshape::basicPolygons[index + selector->getOffset()].renderPolygon(positionX, positionY);
    UISelectable::render();
}
