#include "UISelectableObject.h"
#include "UIObjectSelector.h"
#include "System\graphics\textureManager.h"

UISelectableObject::UISelectableObject(UIObjectSelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                       int _index, Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index, _selectedColor, _hoverColor)
{
}

void UISelectableObject::derivedRender()
{
    if (index > 255) {
        TextureManager::miscellaneous[0].renderTile(positionX, positionY, 0);
    }
    else {
        if (rotation || flipH || flipV)
            TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index,
                1, 1, flipH, flipV,
                rotation * 90, 16, 16);
        else
            TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index);
    }
}

void UISelectableObject::derivedUpdate()
{
}
