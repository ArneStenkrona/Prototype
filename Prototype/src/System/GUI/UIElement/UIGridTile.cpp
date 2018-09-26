#include "UIGridTile.h"
#include "UIGridSelector.h"
#include "System\IO\inputManager.h"

UIGridTile::UIGridTile(UIGridSelector * _selector, int _layer, unsigned int _indX, unsigned int _indY)
    : UIElement(_selector->positionX + indX * 32, _selector->positionY + indY * 32, 32, 32, _layer, true), 
    indX(_indX), indY(_indY), selector(_selector)
{
}

void UIGridTile::render()
{

    UIElement::drawOutlineSquare({ r, g, b, a });
}

void UIGridTile::onMouseOver()
{
    if (getKey(MOUSE_LEFT)) {
        selector->setElement(indX, indY);
    }
    r = 0xff;
    g = 0x00;
    b = 0x00;
    a = 0xff;
}

void UIGridTile::update()
{
    r = 0x00;
    g = 0x00;
    b = 0x00;
    a = 0x40;

    positionX = selector->positionX + indX * 32;
    positionY = selector->positionY + indY * 32;
}
