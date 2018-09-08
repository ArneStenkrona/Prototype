#pragma once

#include <GL/glew.h>
#include "vertexArray.h"
#include "indexBuffer.h"
#include "vertexBufferLayout.h"
#include "shaderGL.h"
#include "frameBuffer.h"
#include "textureGL.h"

class RendererGL {
public:
    RendererGL(unsigned int screen_width, unsigned int screen_height);
    ~RendererGL();
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const ShaderGL& shader) const;
    /*Presents framebuffer*/
    void present();

private:
    FrameBuffer frameBuffer;
};