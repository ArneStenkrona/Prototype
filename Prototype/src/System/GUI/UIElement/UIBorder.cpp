#include "UIBorder.h"
#include <SDL_image.h>
#include "System\graphics\graphicsEngine.h"
#include <iostream>

UIBorder::UIBorder(int _posX, int _posY, int _border_width, int _border_height, int _layer, Color _color)
    : UIElement(_posX, _posY, _border_width, _border_height, _layer, true), color(_color)
{
}

void UIBorder::render()
{
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    SDL_Rect rect = { positionX, positionY, (int)width, (int)height };
    SDL_RenderFillRect(GraphicsEngine::getActiveRenderer(), &rect);
}
