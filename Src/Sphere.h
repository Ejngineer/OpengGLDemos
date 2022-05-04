#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "glad/glad.h"
#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class Sphere
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	std::vector<float> Vertices;
	std::vector<float> TexCoords;
	std::vector<float> Normals;
	std::vector<float> InterleavedVertices;
	std::vector<unsigned int> Indices;

	float radius;
	int sectors;
	int stacks;
	static constexpr float PI = glm::pi<float>();

public:
	//Sphere() = default;
	~Sphere();
	Sphere(float radius = 1.0f, int sectors = 36, int stacks = 18, bool smooth = true);
	void SetUp();
	void Draw();
	void DrawInstanced(int amount);
	void MakeInterleavedVertices();
	void MakeVerticesFlat();
	void MakeVerticesSmooth();
	void clearVectors() 
	{
		std::vector<float>().swap(Vertices);
		std::vector<float>().swap(Normals);
		std::vector<float>().swap(TexCoords);
		std::vector<unsigned int>().swap(Indices);
	};

	std::vector<float> CalcNormal(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3
	);
	void addVertex(float x1, float y1, float z1);
	void addNormal(float x, float y, float z);
	void addTexCoord(float x, float y);
	void addIndices(unsigned int x, unsigned int y, unsigned int z);

	const float* GetVertices() { return Vertices.data(); }
	const float* GetNormals() { return Normals.data(); }
	const float* GetTexCoords() { return TexCoords.data(); }
	const float* GetInterleaved() { return InterleavedVertices.data(); }
	const unsigned int* GetIndices() { return Indices.data(); }

	/*Vertex Array Object Getters*/
	unsigned int GetVAO() { return VAO; }
	unsigned int GetVBO() { return VBO; }
	unsigned int GetEBO() { return EBO; }
};

#endif
