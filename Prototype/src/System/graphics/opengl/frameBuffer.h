#pragma once
#include "GLutility.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "shaderGL.h"
#include "textureGL.h"

class FrameBuffer {
public:
    FrameBuffer(unsigned int screen_width, unsigned int screen_height);
    ~FrameBuffer();

    //Binds the frame buffer (NOTE: DOES NOT BIND THE TEXTURE)
    void bind() const;
    void ubind() const;
    void present() const;
private:
    unsigned int m_renderBufferObject;
    unsigned int m_frameBuffer;
    unsigned int m_TexColorBuffer;

    VertexArray frameBufferVA;
    VertexBuffer frameBufferVB;
    VertexBufferLayout frameBufferLayout;
    IndexBuffer frameBufferIB;

    ShaderGL frameBufferShader;
    
};