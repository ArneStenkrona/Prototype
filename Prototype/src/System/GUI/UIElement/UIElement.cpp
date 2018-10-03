#include "UIElement.h"
#include "System\IO\inputManager.h"
#include "System\graphics\graphicsEngine.h"

std::vector<std::set<UIElement*>> UIElement::allUIElements = std::vector<std::set<UIElement*>>();

UIElement::UIElement(int _posx, int _posy, int _width, int _height, 
                    int _layer, bool _visible)
    : positionX(_posx), positionY(_posy), width(_width), height(_height), 
      layer(_layer), visible(_visible)
{
    if (allUIElements.size() < layer + 1) {
        allUIElements.resize(layer + 1);
    }
    allUIElements[layer].insert(this);
}

UIElement::~UIElement()
{
    allUIElements[layer].erase(this);
}

//helper function
inline bool pointWithin(int px, int py, int posx, int posy,
                        int dimx, int dimy) {
    return px >= posx && px < posx + dimx &&
        py >= posy && py < posy + dimy;
}

void UIElement::updateUIElements()
{
    //Element that mouse is over, if visible
    //If mouse is over more than one element it
    //will prioritize lowest layer number
    //If more than one have the lowest layer number
    //one of them will be picked according to
    //iterator order
    UIElement* selected = nullptr;
    for each (std::set<UIElement*> s in allUIElements) {
        for each (UIElement* e in s) {
            e->update();
            if (!selected && e->visible) {
                int x, y;
                getMouseWorldCoordinates(x, y);
                if (pointWithin(x, y, e->positionX, e->positionY, e->width, e->height)) {
                    selected = e;
                }
            }
        }
    }
    if (selected) {
        selected->onMouseOver();
    }
}

void UIElement::renderUIElements()
{
    for (std::vector<std::set<UIElement*>>::reverse_iterator i = allUIElements.rbegin();
        i != allUIElements.rend(); ++i) {
        for each (UIElement *e in (*i)) {
            if (e->visible) 
                e->render();
        }
    }
}

void UIElement::render()
{
}

void UIElement::onMouseOver()
{
}

void UIElement::update()
{
}

void UIElement::drawOutlineSquare(Color color) {
    SDL_Rect outlineRect = { positionX, positionY, width, height };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &outlineRect);
}

void UIElement::drawSolidSquare(Color color)
{
    SDL_Rect fillRect = { positionX, positionY, width, height};
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(GraphicsEngine::getActiveRenderer(), &fillRect);
}

