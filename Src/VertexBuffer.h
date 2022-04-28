#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "glad/glad.h"

class VertexBuffer
{
private:
	unsigned int _ID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, GLsizeiptr size);
	~VertexBuffer();
	void setDataStaticf(const void* data, GLsizeiptr size);
	void setDataStaticui();
	void Bind();
	void UnBind();
};

#endif