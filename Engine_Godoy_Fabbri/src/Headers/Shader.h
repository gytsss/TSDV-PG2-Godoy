#pragma once

#include <iostream>

class Shader
{
private:
	std::string code;

public:
	Shader(const char* code);
	~Shader();
};