#pragma once
#include "GameObject\Component\graphics\renderer.h"
#include <vector>
#include <set>

class GraphicsEngine {
public:
    //Renderers will render layer by layer

    static void addToRenderQueue(Renderer *r, int layer);
    static void removeFromRenderQueue(Renderer *r, int layer);


    //Renders each layer one by one, 0 is rendered last
    static void updateGraphics();
private:
    static vector<set<Renderer*>> renderQueue;
};
