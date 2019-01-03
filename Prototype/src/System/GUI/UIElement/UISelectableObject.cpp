#include "UISelectableObject.h"
#include "UIObjectSelector.h"
#include "System\graphics\textureManager.h"
#include "World\Tile.h"

UISelectableObject::UISelectableObject(UIObjectSelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                       int _index)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index)
{
}

void UISelectableObject::render()
{
    TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index + selector->getOffset(),
                                                                          1, 1, false, false,
                                                                          0, Tile::TILE_SIZE / 2, Tile::TILE_SIZE / 2);
    UISelectable::render();
}