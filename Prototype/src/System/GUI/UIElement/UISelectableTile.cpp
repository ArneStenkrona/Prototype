#include "UISelectableTile.h"
#include "System\graphics\textureManager.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "UITileSelector.h"
#include "UISelectableTile.h"
#include "World\Tile.h"
#include "System\graphics\graphicsEngine.h"

UISelectableTile::UISelectableTile(UITileSelector* _selector, int _posX, int _posY, unsigned int _layer,
                                   int _index)
    : UISelectable(_selector, _posX, _posY, Tile::TILE_SIZE, Tile::TILE_SIZE, _layer, _index)
{
}

void UISelectableTile::render()
{
    TextureManager::tileMap.texture.renderTile(positionX, positionY, index + selector->getOffset(),
                                                                     1, 1, false, false,
                                                                     0, 16, 16);
    Color borderColor;
    int borderType;

    if (((UITileSelector*)selector)->getBorderColorAndType(index, borderColor, borderType)) {
            SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(),
                borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        switch (borderType)
        {
        case 0:
            UIElement::drawSquare(width, height, borderColor, OUTLINE_SQUARE);
            break;
        case 1: 
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX, positionY + Tile::TILE_SIZE - 1);
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY);
            break;
        case 2:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY);
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX + Tile::TILE_SIZE - 1, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            break;
        case 3:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX + Tile::TILE_SIZE - 1, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY + Tile::TILE_SIZE - 1,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            break;
        case 4:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY + Tile::TILE_SIZE - 1,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX, positionY + Tile::TILE_SIZE - 1);
            break;
        case 5:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY);
            break;
        case 6:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX + Tile::TILE_SIZE - 1, positionY,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            break;
        case 7:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY + Tile::TILE_SIZE - 1,
                positionX + Tile::TILE_SIZE - 1, positionY + Tile::TILE_SIZE - 1);
            break;
        case 8:
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(),
                positionX, positionY,
                positionX, positionY + Tile::TILE_SIZE - 1);
            break;
        default:
            break;
        }
    }

    if (!selector->isActive())
        UIElement::drawSquare(width, height, { 255,255,255,40 });
}

void UISelectableTile::onMouseLeft()
{
    UISelectable::onMouseLeft();
    ((UITileSelector*)selector)->clearHoverIndices();
}
