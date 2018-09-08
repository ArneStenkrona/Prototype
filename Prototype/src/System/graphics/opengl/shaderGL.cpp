#include "shaderGL.h"
#include "GLutility.h"
#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <sstream>


ShaderGL::ShaderGL(const std::string & path): m_FilePath(path),
    m_RenderID(0)
{
    m_RenderID = loadShader(path);
}

ShaderGL::~ShaderGL()
{
    GLCall(glDeleteProgram(m_RenderID));
}

void ShaderGL::bind() const
{
    GLCall(glUseProgram(m_RenderID));
}

void ShaderGL::unbind() const
{
    GLCall(glUseProgram(0));
}

void ShaderGL::setUniform1i(const std::string & name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void ShaderGL::setUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

unsigned int ShaderGL::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int ShaderGL::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //alloca() is bad practice??
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("Failed to compile ");
        printf((type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        printf(" shader.\n");
        printf(message);
        printf("\n");
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int ShaderGL::loadShader(const std::string& path)
{
    std::ifstream stream(path);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return createShader(ss[0].str(), ss[1].str());
}

int ShaderGL::getUniformLocation(const std::string & name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) 
        return m_UniformLocationCache[name];
    
    GLCall(unsigned int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}
