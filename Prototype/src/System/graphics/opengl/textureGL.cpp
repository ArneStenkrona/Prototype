#include "textureGL.h"
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

TextureGL::TextureGL(const std::string & path, unsigned int slot)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), 
      m_Width(0), m_Height(0), m_BPP(0), textureSlot(slot)
{
    assert(("Texture slot 0 is reserved for frame buffer", slot != 0));
    loadTexture();
}

TextureGL::~TextureGL()
{
}

void TextureGL::bind() const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + textureSlot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void TextureGL::unbind() const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + textureSlot));
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool TextureGL::loadTexture()
{
      /* Status indicator */
    bool Status = false;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage[1];

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ((TextureImage[0] = IMG_Load(m_FilePath.c_str())))
    {
        /* Set the status to true */
        Status = true;
        /* Create The Texture */
        GLCall(glGenTextures(1, &m_RendererID));

        /* Typical Texture Generation Using Data From The Bitmap */
        GLCall(glActiveTexture(GL_TEXTURE0 + textureSlot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    
        /* No Filtering */
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        /* Generate The Texture */
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TextureImage[0]->w, TextureImage[0]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[0]->pixels));
        /* unbind */
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
    else {
        printf("Unable to load image %s! SDL_image Error: %s\n", m_FilePath.c_str(), IMG_GetError());
    }
    /* Free up any memory we may have used */
    if (TextureImage[0])
        SDL_FreeSurface(TextureImage[0]);

    return Status;    
}
