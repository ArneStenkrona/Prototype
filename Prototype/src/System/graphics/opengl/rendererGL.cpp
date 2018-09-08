#include "rendererGL.h"
#include "GLutility.h"

RendererGL::RendererGL(unsigned int screen_width, unsigned int screen_height)
    : frameBuffer(FrameBuffer(screen_height, screen_width))
{
    frameBuffer.bind();
}

RendererGL::~RendererGL()
{
}

void RendererGL::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void RendererGL::draw(const VertexArray & va, const IndexBuffer & ib, const ShaderGL & shader) const
{
    frameBuffer.bind();
    shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void RendererGL::present()
{
    frameBuffer.present();
}
