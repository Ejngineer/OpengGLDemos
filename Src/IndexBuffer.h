#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "glad/glad.h"

class IndexBuffer
{
private:
	unsigned int _ID;
public:
	IndexBuffer();
	IndexBuffer(const void* data, GLsizeiptr size);
	~IndexBuffer();
	void setDataStaticf(const void* data, GLsizeiptr size);
	void Bind();
	void UnBind();
};

#endif