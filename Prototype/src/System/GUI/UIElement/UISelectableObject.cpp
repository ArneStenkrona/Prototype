#include "UISelectableObject.h"
#include "UIObjectSelector.h"
#include "System\graphics\textureManager.h"
#include "World\Tile.h"

UISelectableObject::UISelectableObject(UIObjectSelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                       int _index)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index)
{
}

void UISelectableObject::render()
{
    TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index + selector->getOffset(),
                                                                          32 / Tile::TILE_SIZE, 32 / Tile::TILE_SIZE, false, false,
                                                                          0, 16, 16);
    UISelectable::render();
}