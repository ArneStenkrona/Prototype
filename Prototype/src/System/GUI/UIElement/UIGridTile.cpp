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
        UIElement::drawSquare(width, height, {0xFF,0xFF,0xFF,0x08}, OUTLINE);

    }

}

void UIGridTile::onMouseEnter()
{
    selector->setActiveTileCoordinates(indX, indY);

    UISelector* s = UISelector::getActiveSelector();

    if (dynamic_cast<UITileSelector*>(s)) {
        if (getKey(MOUSE_LEFT))
            selector->setTile(indX, indY);
    }

    if (dynamic_cast<UIColliderSelector*>(s)) {
        if (getKey(MOUSE_LEFT))
            selector->setCollider(indX, indY);
    }
}

void UIGridTile::onMouseOver()
{

    UISelector* s = UISelector::getActiveSelector();

    if (dynamic_cast<UITileSelector*>(s)) {
        if (getKeyDown(MOUSE_LEFT))
            selector->setTile(indX, indY);
    }

    if (dynamic_cast<UIColliderSelector*>(s)) {
        if (getKeyDown(MOUSE_LEFT))
            selector->setCollider(indX, indY);
    }

    if (dynamic_cast<UIObjectSelector*>(s)) {
        if (getKeyDown(MOUSE_LEFT))
            selector->setObject(indX, indY);
    }
}

void UIGridTile::onMouseExit()
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
