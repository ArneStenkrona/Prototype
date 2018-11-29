#include "UISelectableTile.h"
#include "System\graphics\textureManager.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "UITileSelector.h"
#include "UISelectableTile.h"
#include "World\Tile.h"

UISelectableTile::UISelectableTile(UITileSelector* _selector, int _posX, int _posY, unsigned int _layer,
                                   int _index)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index)
{
}

void UISelectableTile::render()
{
    TextureManager::tileMap.texture.renderTile(positionX, positionY, index + selector->getOffset(),
                                                                     1, 1, false, false,
                                                                     0, 16, 16);
    Color borderColor = ((UITileSelector*)selector)->withinHover(index) ? selector->getHoverColor() :
        (((UITileSelector*)selector)->withinSelection(index + selector->getOffset()) ?
         selector->getSelectedColor() : COLOR_NONE);

    UIElement::drawSquare(width, height, borderColor, OUTLINE_SQUARE);

    if (!selector->isActive())
        UIElement::drawSquare(width, height, { 255,255,255,40 });
}