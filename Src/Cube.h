#ifndef __CUBE_H__
#define __CUBE_H__

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Cube
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
    const float FixedVertices[32] =
    {
        //-z face
        -0.5f, -0.5f, 0.0f, //0 
         0.5f, -0.5f, 0.0f,//1
         0.5f, 0.5f, 0.0f, //2
        -0.5f, 0.5f, 0.0f, //3

                            //1
         0.5f, -0.5f,-1.0f, //4
         0.5f,  0.5f,-1.0f, //5
                            //2

                           //0
        -0.5f, -0.5f,-1.0f,//6 
        -0.5f,  0.5f,-1.0f,//7 
                           //3
    };

    const unsigned int FixedIndices[24] =
    {
        0,1,2,
        2,3,0,

        1,4,5,
        5,2,1,

        0,6,7,
        7,3,0,

        6,4,5,
        5,7,6,

        //3,2,5,
        //5,7,3,

        //0,1,4,
        //4,6,0
    };
public:
	Cube();
    Cube(float x, float y, float z);
	~Cube() = default;
    void Draw();
    void SetUp();

};

#endif