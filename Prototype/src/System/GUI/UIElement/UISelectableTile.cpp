#include "UISelectableTile.h"
#include "System\graphics\textureManager.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "UITileSelector.h"

UISelectableTile::UISelectableTile(UISelector * _selector, int _posX, int _posY, unsigned int _layer, 
                                   int _index, Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index, _selectedColor, _hoverColor), rotation(0), flipH(0), flipV(0)
{
}

void UISelectableTile::derivedRender()
{
    if (index < 0) {
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

void UISelectableTile::select()
{
    //Forgive me for typecasting
    if ((UITileSelector*)selector)
        return ((UITileSelector*)selector)->getRotationAndFlip(rotation, flipH, flipV);
    else
        printf("COULD NOT UPDATE ROTATION AND FLIP FOR UISelectableTile. \n TYPECAST FAILED. \n");
}

void UISelectableTile::unselect()
{
    rotation = 0;
    flipH = 0;
    flipV = 0;
}
