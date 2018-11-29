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
    UISelectable::render();
}