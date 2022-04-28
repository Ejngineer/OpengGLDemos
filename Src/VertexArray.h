#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "glad/glad.h"

class VertexArray
{
private:
	unsigned int _ID;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
};

#endif