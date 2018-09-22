#include "UIBorder.h"
#include <SDL_image.h>
#include "System\graphics\graphicsEngine.h"
#include <iostream>

UIBorder::UIBorder(int _posX, int _posY, int _border_width, int _border_height, int _layer)
    : UIElement(_posX, _posY, _border_width, _border_height, _layer, true)
{
}

void UIBorder::render()
{
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), 160, 160, 160, 255);
    SDL_Rect rect = { positionX, positionY, width, height };
    SDL_RenderFillRect(GraphicsEngine::getActiveRenderer(), &rect);
}
