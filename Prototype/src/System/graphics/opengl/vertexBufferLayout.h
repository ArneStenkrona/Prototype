#pragma once
#include <vector>
#include <GL\glew.h>
#include "GLutility.h"


struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void push(unsigned int count) {
        static_assert(false);
    }

    template<>
    void push<float>(unsigned int count) {
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += count * sizeof(GLfloat);
    }

    template<>
    void push<unsigned int>(unsigned int count) {
        m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
        m_Stride += count * sizeof(GLuint);
    }

    template<>
    void push<unsigned char>(unsigned int count) {
        m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
        m_Stride += count * sizeof(GLubyte);
    }

    inline std::vector<VertexBufferElement>getElements() const { return m_Elements; }
    inline const unsigned int getStride() const { return m_Stride; }


private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

};