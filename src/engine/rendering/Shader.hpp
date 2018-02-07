#include "GL/glew.h"
#include <string>

class Shader
{
public:
    Shader(const std::string &filePath);
    virtual ~Shader();

    GLuint GetProgramId();

private:
    void LoadShader(const std::string &filePath);

    GLuint m_shader;
    GLuint m_program;
};