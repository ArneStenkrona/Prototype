#include "UIColliderSelector.h"
#include "System\IO\inputManager.h"

UIColliderSelector::UIColliderSelector(int _posx, int _posy, int _layer, unsigned int _columns, unsigned int _rows)
    : UIElement(_posx, _posy, 32 * _columns, 32 * _rows, _layer, false),
    columns(_columns), rows(_rows), indX(0), indY(0)
{
    colliders.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        colliders[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            colliders[i][j] = new UISelectCollider(this, positionX + (i * 32), positionY + (j * 32),
                layer, i + (16 * j));
        }
    }
}

UIColliderSelector::~UIColliderSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(colliders[i][j]);
        }
    }
}

void UIColliderSelector::moveIndices(int dx, int dy)
{
    //if (indX + columns + dx <= 16 && indX + dx >= 0) indX += dx;
    //if (indY + rows + dy <= 16 && indY + dy >= 0) indY += dy;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            colliders[i][j]->setColliderIndex(indX + i + (16 * (indY + j)));
        }
    }
}

void UIColliderSelector::update()
{
    if (getKey(INPUT_KEY_LCTRL)) {
        int dX = 0;
        int dY = 0;

        if (getKeyDown(INPUT_KEY_W)) {
            dY -= 1;
        }
        if (getKeyDown(INPUT_KEY_S)) {
            dY += 1;
        }
        if (getKeyDown(INPUT_KEY_A)) {
            dX -= 1;
        }
        if (getKeyDown(INPUT_KEY_D)) {
            dX += 1;
        }
        if (dX || dY) moveIndices(dX, dY);
    }
}
