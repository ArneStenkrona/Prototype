#include "UITileSelector.h"
#include "System\IO\inputManager.h"

UITileSelector::UITileSelector(int _posx, int _posy, int _layer,
                              unsigned int _columns, unsigned int _rows)
    : UIElement(_posx, _posy, 32 * _columns, 32 * _rows, _layer, false),
      columns(_columns), rows(_rows), indX(0), indY(0), rotation(0)
{
    tiles.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        tiles[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            tiles[i][j] = new UISelectTile(this, positionX + (i * 32), positionY + (j * 32),
                                     layer, i + (16 * j));
        }
    }
    tiles[columns].resize(1);
    tiles[columns][0] = new UISelectTile(this, positionX + (columns * 32), positionY,
                                   layer, -1);
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
    if (indX + columns + dx <= 16 && indX + dx >= 0) indX += dx;
    if (indY + rows + dy <= 16 && indY + dy >= 0) indY += dy;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            tiles[i][j]->setTileIndex(indX + i + (16 * (indY + j)) );
        }
    }
}

void UITileSelector::update()
{
    if (getKeyDown(INPUT_KEY_R)) {
        rotation = (rotation + 1) % 4;
    }
}
