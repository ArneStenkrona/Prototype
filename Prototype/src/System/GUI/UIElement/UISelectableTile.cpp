#include "UISelectableTile.h"
#include "System\graphics\textureManager.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "UITileSelector.h"
#include "UISelectableTile.h"
#include "World\Tile.h"

UISelectableTile::UISelectableTile(UITileSelector* _selector, int _posX, int _posY, unsigned int _layer,
                                   int _index, Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index, _selectedColor, _hoverColor), rotation(0), flipH(0), flipV(0),
      tSelector(_selector)
{
}

void UISelectableTile::derivedRender()
{
    if (index > 255) {
        TextureManager::miscellaneous[0].renderTile(positionX, positionY, 0);
    }
    else {
        if (rotation || flipH || flipV)
            TextureManager::tileMap.texture.renderTile(positionX, positionY, index,
                1, 1, flipH, flipV,
                rotation * 90, 16, 16);
        else
            TextureManager::tileMap.texture.renderTile(positionX, positionY, index);
    }
}

void UISelectableTile::derivedUpdate()
{
    if (selector->getSelectedIndex() == index)
        tSelector->getRotationAndFlip(rotation, flipH, flipV);
    else {
        rotation = 0;
        flipH = false;
        flipV = false;
    }
}