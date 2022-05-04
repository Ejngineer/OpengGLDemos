#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad/glad.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Shader
{
private:
	unsigned int _ID;

public:
	Shader() = default;
	~Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void setInt1i(const char* uniform, int value);
	void setFloat1f(const  char* uniform, float value);
	void setDouble1d(const char* uniform, double value);
	void setInt3i(const char* uniform, int v0, int v1, int v2);
	void setInt3iv(const char* uniform, glm::vec3 values);
	void setFloat3f(const char* uniform, float v0, float v1, float v2);
	void setFloat3fv(const char* uniform, glm::vec3 values);
	void setDouble3d(const char* uniform, double v0, double v1, double v2);
	void setDouble3dv(const char* uniform, glm::vec3 values);
	void setMat4f(const char* uniform, glm::mat4 mat);
	void use();
};

#endif