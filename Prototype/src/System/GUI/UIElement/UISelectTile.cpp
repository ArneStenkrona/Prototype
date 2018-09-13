#include "UISelectTile.h"
#include "System\graphics\lTexture.h"
#include "World\editor\editor.h"
#include "System\IO\inputManager.h"
#include "World\editor\editor.h"
#include "System\graphics\graphicsEngine.h"
#include "UITileSelector.h"

UISelectTile::UISelectTile(UITileSelector* _selector, int _posx, int _posy,
               unsigned int _layer, int _tileIndex)
    : UIElement(_posx, _posy, 32, 32, _layer, true), tileIndex(_tileIndex),
      selector(_selector)
{
}

void UISelectTile::render()
{

    if (tileIndex < 0) {
        TextureManager::miscellaneous[0].renderTile(positionX, positionY, 0);
    }
    else {
        TextureManager::tileMap.texture.renderTile(positionX, positionY, tileIndex);
    }
    UIElement::drawOutlineSquare(positionX, positionY, r, g, b, a);
}

void UISelectTile::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT)) {
        selector->setIndex(tileIndex);
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

void UISelectTile::update()
{
    if (selector->getSelectedIndex() == tileIndex) {
        r = 0x00;
        g = 0xff;
        b = 0x00;
        a = 0xff;
    }
    else {
        r = 0x00;
        g = 0x00;
        b = 0x00;
        a = 0x00;
    }
}
