#include "UIColliderSelector.h"
#include "System\IO\inputManager.h"
#include "..\UISelectable\UISelectableCollider.h"
#include "World\Tile.h"

UIColliderSelector::UIColliderSelector(int _posx, int _posy, int _layer, 
                                       unsigned int _columns, unsigned int _rows,
                                       Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 8, 8, "COLLIDERS", _selectedColor, _hoverColor)
{
    selectables.resize(columns);
    for (unsigned int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (unsigned int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableCollider(this, positionX + (i * Tile::TILE_SIZE), 
                                                         LABEL_HEIGHT + positionY + (j * Tile::TILE_SIZE),
                                                         layer + 1, i + (indexLimitX * j));
        }
    }
}

std::optional<Polyshape> UIColliderSelector::getPolygon() const
{
    if (Polyshape::basicPolygons.size() > selectedIndex) {
        Polyshape pg = Polyshape::basicPolygons[selectedIndex];
        if (rotation) pg = pg.rotate(90 * rotation, Point(Tile::TILE_SIZE / 2, Tile::TILE_SIZE / 2));
        if (flipH || flipV) pg = pg.mirror(flipH, flipV, Point(Tile::TILE_SIZE, Tile::TILE_SIZE));
        return pg;
    }
    else
        return {};
}

void UIColliderSelector::renderSelected(int x, int y, Color color)
{
    UIElement::drawSquare(width, height, { 0, 0, 0, 255 });
    if (Polyshape::basicPolygons.size() > selectedIndex) {
        Polyshape pg = Polyshape::basicPolygons[selectedIndex];
        if (rotation) pg = pg.rotate(90 * rotation, Point(Tile::TILE_SIZE / 2, Tile::TILE_SIZE / 2));
        if (flipH || flipV) pg = pg.mirror(flipH, flipV, Point(Tile::TILE_SIZE, Tile::TILE_SIZE));
        pg.renderPolygon(x, y, color);
    }
}
