#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &_ID);
	Bind();
}

IndexBuffer::IndexBuffer(const void* data, GLsizeiptr size)
{
	glGenBuffers(1, &_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_ID);
}

void IndexBuffer::setDataStaticf(const void* data, GLsizeiptr size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
