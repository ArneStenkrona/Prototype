#include "Gameobject/gameObject.h"
#include "lineRenderer.h"
#include <iostream>
#include "System\graphics\graphicsEngine.h"
LineRenderer::LineRenderer(GameObject * _object) : Renderer(_object), thickness(1)
{
}

void LineRenderer::render()
{
    //Check if camera is available
    if (cameraPosition != nullptr) {
        Point cameraPos = cameraPosition->position;
        Point start = a - cameraPos;
        Point end = b - cameraPos;
        SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), m_r, m_g, m_b, m_a);
        for (unsigned int i = 0; i < thickness; i++) {
            Point offset = Point((i - thickness / 2), 0);
            Point st = start + offset;
            Point en = end + offset;
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(), (int)st.x, (int)st.y, (int)en.x, (int)en.y);
        }
        for (unsigned int i = 0; i < thickness; i++) {
            Point offset = Point(0, (i - thickness / 2));
            Point st = start + offset;
            Point en = end + offset;
            SDL_RenderDrawLine(GraphicsEngine::getActiveRenderer(), (int)st.x, (int)st.y, (int)en.x, (int)en.y);
        }
    }
    else {
        std::cout << "No camera has been set for rendering" << std::endl;
    }
}

void LineRenderer::setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
    m_r = _r;
    m_g = _g;
    m_b = _b;
    m_a = _a;
}
