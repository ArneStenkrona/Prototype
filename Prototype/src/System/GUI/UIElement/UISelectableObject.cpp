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
        TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(positionX, positionY, index,
            1, 1, false, false,
            0, 16, 16);
}

void UISelectableObject::derivedUpdate()
{
}
