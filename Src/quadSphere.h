#ifndef __QUADSPHERE_H__
#define __QUADSPHERE_H__

#include "glad/glad.h"
#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class quadSphere
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	std::vector<float> Vertices;
	std::vector<float> TexCoords;
	std::vector<float> Normals;
	std::vector<float> Tangents;
	std::vector<float> BiTangents;

	std::vector<float> InterleavedVertices;
	std::vector<unsigned int> Indices;

	float radius;
	int sectors;
	int stacks;
	bool smooth;
	static constexpr float PI = glm::pi<float>();
public:
	//Sphere() = default;
	~quadSphere();
	quadSphere(float radius = 1.0f, int sectors = 36, int stacks = 18, bool smooth = true);
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
		std::vector<float>().swap(Tangents);
		std::vector<float>().swap(BiTangents);
		std::vector<float>().swap(TexCoords);
		std::vector<unsigned int>().swap(Indices);
	};

	std::vector<float> CalcNormal(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3
	);

	std::vector<float> CalcTangent(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float uv1x, float uv1y,
		float uv2x, float uv2y,
		float uv3x, float uv3y
	);

	void addVertex(float x1, float y1, float z1);
	void addNormal(float x, float y, float z);
	void addTangent(float x, float y, float z);
	void addBiTangent(float x, float y, float z);
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
