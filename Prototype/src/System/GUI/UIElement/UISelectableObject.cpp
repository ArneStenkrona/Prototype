#include "UISelectableObject.h"
#include "UIObjectSelector.h"
#include "System\graphics\textureManager.h"

UISelectableObject::UISelectableObject(UIObjectSelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                       int _index)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index)
{
}

void UISelectableObject::render()
{
    TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index + selector->getOffset(),
                                                                          1, 1, false, false,
                                                                          0, 16, 16);
    UISelectable::render();
}