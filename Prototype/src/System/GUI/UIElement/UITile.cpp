#include "UITile.h"
#include "System\graphics\lTexture.h"
#include "World\editor\editor.h"
#include "System\IO\inputManager.h"
#include "World\editor\editor.h"
#include "System\graphics\graphicsEngine.h"
#include "UITileSelector.h"

UITile::UITile(UITileSelector* _selector, int _posx, int _posy,
               unsigned int _layer, unsigned int _tileIndex)
    : UIElement(_posx, _posy, 32, 32, _layer, true), tileIndex(_tileIndex),
      selector(_selector)
{
}

void drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Rect outlineRect = { x, y, 32, 32 };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), r, g, b, a);
    SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &outlineRect);
}

void UITile::render()
{
    TextureManager::tileMap.texture.renderTile(positionX, positionY, tileIndex);
    drawOutlineSquare(positionX, positionY, r, g, b, a);
}

void UITile::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT)) {
        selector->setIndex(tileIndex);
        r = 0x00;
        g = 0xff;
        b = 0x00;
        a = 0xff;
    }
    else {
        r = 0x00;
        g = 0xff;
        b = 0xff;
        a = 0xff;
    }
}

void UITile::update()
{
    if (selector->getIndex() == tileIndex) {
        r = 0x00;
        g = 0xff;
        b = 0x00;
        a = 0xff;
    }
    else {
        r = 0x00;
        g = 0x00;
        b = 0x00;
        a = 0x00;
    }
}
