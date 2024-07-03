#include "Shader.h"

#include <glew.h>
#include <glm/vec3.hpp>

Shader::Shader(const char* code)
{
}

Shader::~Shader()
{
}

void setVec3(GLuint shaderProgramID, const std::string& uniformName, const glm::vec3& value)
{
    GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (location != -1)
    {
        glUniform3f(location, value.x, value.y, value.z);
    }
}

void setFloat(GLuint shaderProgramID, const std::string& uniformName, float value)
{
    GLint location = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (location != -1)
    {
        glUniform1f(location, value);
    }
}
