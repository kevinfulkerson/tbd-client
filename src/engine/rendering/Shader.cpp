#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const std::string &filePath) : m_shader(0),
                                              m_program(0)
{
    this->LoadShader(filePath);
}

/* virtual */ Shader::~Shader()
{
    glDetachShader(this->m_program, this->m_shader);
    glDeleteShader(this->m_shader);
    glDeleteProgram(this->m_program);
}

GLuint Shader::GetProgramId()
{
    return this->m_program;
}

void Shader::LoadShader(const std::string &filePath)
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
        return;
    }

    GLint result = GL_FALSE;
    int infoLogLength = 0;

    GLuint tempShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (tempShaderId == 0)
    {
        // Could not create a shader
        return;
    }

    char const *codeStrPointer = shaderCode.c_str();
    glShaderSource(tempShaderId, 1, &codeStrPointer, NULL);
    glCompileShader(tempShaderId);

    glGetShaderiv(tempShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(tempShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (result == GL_FALSE && infoLogLength != 0)
    {
        // Could not compile the shader
        glDeleteShader(tempShaderId);
        return;
    }

    GLuint tempProgramId = glCreateProgram();
    if (tempProgramId == 0)
    {
        // Could not create a program object
        // The shader wasn't attached, so just delete the shader
        glDeleteShader(tempShaderId);
        return;
    }

    glAttachShader(tempProgramId, tempShaderId);
    glLinkProgram(tempProgramId);

    glGetProgramiv(tempProgramId, GL_LINK_STATUS, &result);
    glGetProgramiv(tempProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (result == GL_FALSE && infoLogLength != 0)
    {
        // Could not link the program
        glDetachShader(tempProgramId, tempShaderId);
        glDeleteShader(tempShaderId);
        return;
    }

    // Otherwise, we have a working shader program
    printf("here\n");
    this->m_program = tempProgramId;
    this->m_shader = tempShaderId;
}