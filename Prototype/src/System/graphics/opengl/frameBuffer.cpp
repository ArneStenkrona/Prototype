#include "frameBuffer.h"

float positions[] = {
    -0.0f, -0.0f, 0.0f, 1.0f,
    1.0f, -0.0f, 1.0f, 1.0f,
    1.0f,  1.0f, 1.0f, 0.0f,
    -0.0f,  1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

FrameBuffer::FrameBuffer(unsigned int screen_width, unsigned int screen_height)
    : m_frameBuffer(0), m_TexColorBuffer(0), frameBufferShader(ShaderGL("Assets/shaders/TextureShader.shader")),
    frameBufferIB(IndexBuffer(indices, 6)), frameBufferVB(VertexBuffer(positions, 4 * 4 * sizeof(float))),
    m_renderBufferObject(0)
{
    GLCall(glGenFramebuffers(1, &m_frameBuffer));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));
    
    //Generate screen texture 
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glGenTextures(1, &m_TexColorBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_TexColorBuffer));
    frameBufferShader.setUniform1i("u_Texture", 0);
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

    //Set GL parameters 
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexColorBuffer, 0));

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    
    frameBufferLayout.push<float>(2);
    frameBufferLayout.push<float>(2);
    frameBufferVA.addBuffer(frameBufferVB, frameBufferLayout);
}

FrameBuffer::~FrameBuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_frameBuffer));
}

void FrameBuffer::present() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    frameBufferShader.bind();
    frameBufferVA.bind();
    frameBufferIB.bind();
    GLCall(glDrawElements(GL_TRIANGLES, frameBufferIB.getCount(), GL_UNSIGNED_INT, nullptr));
}

void FrameBuffer::bind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));
}

void FrameBuffer::ubind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
