#pragma once
#include "GLutility.h"
#include <string>

class TextureGL {
public:
    TextureGL(const std::string& path, unsigned int slot);
    ~TextureGL();

    void bind() const;
    void unbind() const;

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }

    bool loadTexture();
    
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

    unsigned int textureSlot;
};