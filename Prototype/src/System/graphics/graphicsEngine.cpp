#pragma once
#include "System\graphics\graphicsEngine.h"
#include <vector>

using namespace::std;
vector<set<Renderer*>> GraphicsEngine::renderQueue = vector<set<Renderer*>>();

void GraphicsEngine::addToRenderQueue(Renderer *r, int layer) {  
    if (renderQueue.size() < layer + 1) renderQueue.resize(layer + 1);
    renderQueue[layer].insert(r);
}

void GraphicsEngine::removeFromRenderQueue(Renderer * r, int layer)
{
    if (renderQueue.size() > layer)
        renderQueue[layer].erase(r);
}

void GraphicsEngine::updateGraphics()
{
    for (vector<set<Renderer*>>::reverse_iterator i = renderQueue.rbegin();
        i != renderQueue.rend(); ++i) {
        for each (Renderer *r in (*i)) {
            r->render();
        }
    }
}
