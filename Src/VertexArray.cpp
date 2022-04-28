#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_ID);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_ID);
}

void VertexArray::Bind()
{
	glBindVertexArray(_ID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
