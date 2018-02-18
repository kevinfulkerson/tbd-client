#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <vector>

#include "GL/glew.h"

namespace tbd
{
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
}

#endif //_SHADER_H_