#include "Cube.h"

Cube::Cube()
{
	VBO.Bind();
	IBO.Bind();
	VBO.setDataStaticf(FixedVertices, sizeof(FixedVertices));
	IBO.setDataStaticf(FixedIndices, sizeof(FixedIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Cube::Cube(float x, float y, float z)
{
    const float Vertices[] =
    {
        //-z face
        -x/2.0f,-y/2.0f, z/2.0f, 
         x/2.0f,-y/2.0f, z/2.0f,
         x/2.0f, y/2.0f, z/2.0f,
        -x/2.0f, y/2.0f, z/2.0f,
         x/2.0f,-y/2.0f,-z/2.0f,
         x/2.0f, y/2.0f,-z/2.0f, 
        -x/2.0f,-y/2.0f,-z/2.0f,
        -x/2.0f, y/2.0f,-z/2.0f,
    };

    VBO.Bind();
    IBO.Bind();

    VBO.setDataStaticf(Vertices, sizeof(Vertices));
    IBO.setDataStaticf(FixedIndices, sizeof(FixedIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Cube::Draw()
{
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    VAO.UnBind();
}

void Cube::SetUp()
{
    VBO.Bind();
    IBO.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
