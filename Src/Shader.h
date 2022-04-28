#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad/glad.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
private:
	unsigned int _ID;

public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void use();
};

#endif