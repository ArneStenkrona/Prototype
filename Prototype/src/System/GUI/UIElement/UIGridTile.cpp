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
            TextureManager::spriteSheets[TextureManager::TOOL_ICONS].renderTile(positionX, positionY, 1, 1, 1, false, false, 0, 0, 0, { 255, 255, 255, 160 });
            break;
        }
    }

    UIElement::drawSquare(width, height, { r, g, b, a }, OUTLINE_SQUARE);
}

void UIGridTile::onMouseOver()
{
    selector->setActiveTileCoordinates(indX, indY);

    if (getKey(MOUSE_LEFT)) {
        selector->setElement(indX, indY);
    }
    r = 0xff;
    g = 0x00;
    b = 0x00;
    a = 0xff;
}

void UIGridTile::onMouseLeft()
{
    selector->setActiveTileCoordinates(-1, -1);
}

void UIGridTile::update()
{
    r = 0x00;
    g = 0x00;
    b = 0x00;
    a = 0x40;
}

void UIGridTile::onSelect()
{
    selector->selected = true;
}

void UIGridTile::onDeselect()
{
    selector->selected = false;
}
