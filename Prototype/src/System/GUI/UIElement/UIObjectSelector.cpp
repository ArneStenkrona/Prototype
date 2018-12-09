#include "UIObjectSelector.h"
#include "UISelectableObject.h"
#include "System\graphics\textureManager.h"
#include "World\Tile.h"
#include "System\graphics\graphicsEngine.h"

UIObjectSelector::UIObjectSelector(int _posx, int _posy, int _layer, unsigned int _columns, unsigned int _rows, Color _selectedColor, Color _hoverColor)
    :UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16, "OBJECTS", _selectedColor, _hoverColor)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableObject(this,
                                                       positionX + (i * 32),
                                                       LABEL_HEIGHT + positionY + (j * 32),
                                                       layer + 1, i + (indexLimitX * j));
        }
    }
}

UIObjectSelector::~UIObjectSelector()
{
}

void UIObjectSelector::renderSelected(int x, int y, Color color)
{
        TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(x, y, selectedIndex,
                                                                   32 / Tile::TILE_SIZE, 32 / Tile::TILE_SIZE,
                                                                   flipH, flipV,
                                                                   rotation * 90, 16, 16,
                                                                   color);
        Color c = COLOR_PINK;
        SDL_Rect rect = { x, y, 32 , 32 };
        SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), c.r, c.g, c.b, c.a);
        SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &rect);
}
