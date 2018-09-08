#pragma once
#include "renderer.h"

class GameObject;
class LineRenderer : public Renderer {
public:
    LineRenderer(GameObject *_object);
    void render();
    void setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);

    Point a;
    Point b;
    unsigned int thickness;
private:
    //color
    unsigned char m_r, m_g, m_b, m_a;
};