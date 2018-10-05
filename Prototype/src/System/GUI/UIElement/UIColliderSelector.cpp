#include "UIColliderSelector.h"
#include "System\IO\inputManager.h"
#include "UISelectableCollider.h"
#include "World\Tile.h"

UIColliderSelector::UIColliderSelector(int _posx, int _posy, int _layer, 
                                       unsigned int _columns, unsigned int _rows,
                                       Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 8, 8)
{
    selectables.resize(columns);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableCollider(this, positionX + (i * Tile::TILE_SIZE), positionY + (j * Tile::TILE_SIZE),
                                                         layer + 1, i + (indexLimitX * j), _selectedColor, _hoverColor);
        }
    }
}

UIColliderSelector::~UIColliderSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(selectables[i][j]);
        }
    }
}

std::optional<Polyshape> UIColliderSelector::getPolygon() const
{
    if (Polyshape::basicPolygons.size() > selectedIndex)
        return Polyshape::basicPolygons[selectedIndex];
    else
        return {};
}