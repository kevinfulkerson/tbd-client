#include "GL/glew.h"
#include <string>
#include <vector>

class Shader
{
public:
    Shader();
    virtual ~Shader();

    GLuint GetProgramId();
    void DeleteProgram();
    void AddShader(const std::string &filePath, const GLenum shaderType);
    void LinkProgram();

private:
    bool loadShader(const std::string &filePath, const GLuint shaderId);

    GLuint m_program;
    std::vector<GLuint> m_shaders;
};