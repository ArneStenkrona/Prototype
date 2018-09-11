#include "UITileSelector.h"

UITileSelector::UITileSelector(int _posx, int _posy, unsigned int _layer,
                              unsigned int _columns, unsigned int _rows)
    : UIElement(_posx, _posy, 32 * _columns, 32 * _rows, _layer, false),
      columns(_columns), rows(_rows)
{
    tiles.resize(columns);
    for (int i = 0; i < columns; i++) {
        tiles[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            tiles[i][j] = new UITile(this, positionX + (i * 32), positionY + (j * 32),
                                     layer, i + (16 * j));
        }
    }
}

UITileSelector::~UITileSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(tiles[i][j]);
        }
    }
}

void UITileSelector::moveIndices(int dx, int dy)
{
    if (dx > 0) {
        if (indX + columns + 1 < 16)
            indX++;
    }
    else if (dx < 0) {
        if (indX - 1 > 0)
            indX--;
    }
    if (dy > 0) {
        if (indY + rows + 1 < 16)
            indY++;
    }
    else if (dy < 0) {
        if (indY - 1 > 0)
            indY--;
    }

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            tiles[i][j]->setTileIndex(indX + i + (32 * (indY + j)) );
        }
    }
}
