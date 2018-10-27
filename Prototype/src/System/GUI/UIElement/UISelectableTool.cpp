#include "UISelectableTool.h"
#include "UIToolSelector.h"
#include "System\graphics\textureManager.h"

UISelectableTool::UISelectableTool(UIToolSelector * _selector, int _posX, int _posY, 
                                   unsigned int _layer, int _index, 
                                   Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index, _selectedColor, _hoverColor)
{
}

void UISelectableTool::derivedRender()
{
    TextureManager::miscellaneous[0].renderTile(positionX, positionY, 0);
}
