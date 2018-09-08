#pragma once
#include <string>
#include <unordered_map>

class ShaderGL {
public:
    ShaderGL(const std::string& path);
    ~ShaderGL();

    void bind() const;
    void unbind() const;

    // Set uniforms
    void setUniform1i(const std::string& name, int value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
    //parses file and creates shader
    //returns shaderID
    static unsigned int loadShader(const std::string& path);
    //helper functions
    static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    static unsigned int compileShader(unsigned int type, const std::string& source);
    
    int getUniformLocation(const std::string& name);
    
    const std::string& m_FilePath;
    unsigned int m_RenderID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};