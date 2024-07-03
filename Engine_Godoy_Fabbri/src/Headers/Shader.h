#pragma once

#include <glew.h>
#include <iostream>
#include <glm/vec3.hpp>

class Shader
{
private:
	std::string code;

public:
	Shader(const char* code);
	~Shader();
	void setVec3(GLuint shaderProgramID, const std::string& uniformName, const glm::vec3& value);
	void setFloat(GLuint shaderProgramID, const std::string& uniformName, float value);
};
