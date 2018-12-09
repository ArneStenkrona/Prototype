#include "UIGridTile.h"
#include "UIGridSelector.h"
#include "System\IO\inputManager.h"

UIGridTile::UIGridTile(UIGridSelector * _selector, int _layer, unsigned int _indX, unsigned int _indY)
    : UIElement(_selector->positionX + indX * Tile::TILE_SIZE, _selector->positionY + indY * Tile::TILE_SIZE, 
                Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, true),
                indX(_indX), indY(_indY), selector(_selector)
{
}

void UIGridTile::updatePosition()
{
    positionX = selector->roomPosX + indX * Tile::TILE_SIZE;
    positionY = selector->roomPosY + indY * Tile::TILE_SIZE;
}

void UIGridTile::render()
{
    if (mouseOver()) {
        switch (selector->getTool()) {
        case UIToolSelector::PLACE_TOOL:
            UISelector::getActiveSelector()->renderSelected(positionX, positionY, { 255, 255, 255, 160 });
            break;
        case UIToolSelector::DELETE_TOOL:
            TextureManager::spriteSheets[TextureManager::TOOL_ICONS].renderTile(positionX, positionY, 31, 1, 1, false, false, 0, 0, 0, { 255, 255, 255, 160 });
            //UIElement::drawSquare(width, height, COLOR_RED, OUTLINE_SQUARE);
            break;
        }
    }
    else {
        UIElement::drawSquare(width, height, {0xFF,0xFF,0xFF,0x08}, OUTLINE_SQUARE);

    }

}

void UIGridTile::onMouseOver()
{
    selector->setActiveTileCoordinates(indX, indY);

    if (getKey(MOUSE_LEFT)) {
        selector->setElement(indX, indY);
    }
}

void UIGridTile::onMouseLeft()
{
    selector->setActiveTileCoordinates(-1, -1);
}

void UIGridTile::update()
{
}

void UIGridTile::onSelect()
{
    selector->selected = true;
}

void UIGridTile::onDeselect()
{
    selector->selected = false;
}
