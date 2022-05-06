#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "glad/glad.h"
#include <string>
#include <iostream>

class Texture
{
private:
	unsigned int m_ID;
public:
	Texture();
	Texture(const std::string& path);
	~Texture();
	int Load(const std::string& path);
	void ActivateTexture2D(unsigned int index);
	void ActivateTextureCube(int index);
	void Bind();
	void UnBind();
};

#endif