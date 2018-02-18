#include "src/engine/rendering/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Shader::Shader() : m_program(0),
                   m_shaders(0)
{
}

/* virtual */ Shader::~Shader()
{
}

GLuint Shader::GetProgramId()
{
    return this->m_program;
}

void Shader::DeleteProgram()
{
    glDeleteProgram(this->m_program);
}

void Shader::AddShader(const std::string &filePath, const GLenum shaderType)
{
    GLuint tempShaderId = glCreateShader(shaderType);
    if (tempShaderId == 0)
    {
        // Could not create a shader
        return;
    }
    
    if (this->loadShader(filePath, tempShaderId))
    {
        if (this->m_program == 0)
        {
            this->m_program = glCreateProgram();
            if (this->m_program == 0)
            {
                // Could not create a program object
                return;
            }
        }

        this->m_shaders.push_back(tempShaderId);
    }
}

void Shader::LinkProgram()
{
    GLint result = GL_FALSE;
    int infoLogLength = 0;

    auto it = this->m_shaders.begin();
    auto end = this->m_shaders.end();
    for (; it != end; ++it)
    {
        glAttachShader(this->m_program, *it);
    }

    glLinkProgram(this->m_program);

    glGetProgramiv(this->m_program, GL_LINK_STATUS, &result);
    glGetProgramiv(this->m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (result == GL_FALSE && infoLogLength != 0)
    {
        // Could not link the program
        std::vector<GLchar> errorLog(infoLogLength);
	    glGetProgramInfoLog(this->m_program, infoLogLength, &infoLogLength, &errorLog[0]);
        std::cout << "glLinkProgram: Failed with:" << 
            std::string(errorLog.begin(), errorLog.end()) << std::endl;
    }

    it = this->m_shaders.begin();
    end = this->m_shaders.end();
    for (; it != end; ++it)
    {
        glDetachShader(this->m_program, *it);
        glDeleteShader(*it);
    }
}

bool Shader::loadShader(const std::string &filePath, const GLuint shaderId)
{
    std::string shaderCode;
    std::ifstream shaderStream(filePath, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else
    {
        // Could not load the file
        std::cout << "Failed to open shader file." << std::endl;
        return false;
    }

    GLint result = GL_FALSE;
    GLint infoLogLength = 0;

    char const *codeStrPointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &codeStrPointer, NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (result == GL_FALSE && infoLogLength != 0)
    {
        // Could not compile the shader
        std::vector<GLchar> errorLog(infoLogLength);
	    glGetShaderInfoLog(shaderId, infoLogLength, &infoLogLength, &errorLog[0]);
        std::cout << "glCompileShader: Failed with:" << 
            std::string(errorLog.begin(), errorLog.end()) << std::endl;

        glDeleteShader(shaderId);
        return false;
    }

    return true;
}