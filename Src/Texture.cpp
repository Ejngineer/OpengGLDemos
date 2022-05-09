#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	glGenTextures(1, &m_ID);
}

Texture::Texture(const std::string& path)
{
	glGenTextures(1, &m_ID);
	Load(path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

int Texture::Load(const std::string& path)
{
	int width, height, channels;
	unsigned char* img = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (img == NULL)
	{
		std::cout << "ERROR::FAILED_TO_LOAD_IMAGE" << std::endl;
		return -1;
	}
	else
	{
		GLenum Format;
		if (channels == 4)
		{
			Format = GL_RGBA;
		}
		else
		{
			Format = GL_RGB;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, Format, width, height, 0, Format, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	stbi_image_free(img);



	return 0;
}

void Texture::ActivateTexture2D(unsigned int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
