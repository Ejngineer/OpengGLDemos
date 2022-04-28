#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &_ID);
	Bind();
}

VertexBuffer::VertexBuffer(const void* data, GLsizeiptr size)
{
	glGenBuffers(1, &_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_ID);
}

void VertexBuffer::setDataStaticf(const void* data, GLsizeiptr size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
