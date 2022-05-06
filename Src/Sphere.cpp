#include "Sphere.h"

const int MIN_SECTORS = 3;
const int MIN_STACKS = 2;

Sphere::~Sphere()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

Sphere::Sphere(float radius, int sectors, int stacks, bool smooth)
{
	this->radius = radius;
	this->sectors = sectors;
	this->smooth = smooth;
	if (sectors < MIN_SECTORS)
		this->sectors = MIN_SECTORS;

	this->stacks = stacks;

	if (stacks < MIN_STACKS)
		this->stacks = MIN_STACKS;

	if (smooth)
	{
		MakeVerticesSmooth();
	}
	else 
	{
		MakeVerticesFlat();
	}
}

void Sphere::SetUp()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (unsigned int)InterleavedVertices.size() * sizeof(float), GetInterleaved(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)Indices.size() * sizeof(unsigned int), GetIndices(), GL_STATIC_DRAW);

	if(!smooth)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	}
	else
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	}
}

void Sphere::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (unsigned int)Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sphere::DrawInstanced(int amount)
{
	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, (unsigned int)Indices.size(), GL_UNSIGNED_INT, 0, amount);
	glBindVertexArray(0);
}


void Sphere::MakeVerticesFlat()
{
	struct Vertex
	{
		float x, y, z, s, t;
	};

	float xy, z;

	float sectorAngle, stackAngle;
	float sectorStep = 2 * PI / sectors;
	float stackStep = PI / stacks;

	std::vector<Vertex> tmpVertices;

	for (int i = 0; i <= stacks; i++)
	{
		stackAngle = PI/2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectors; j++)
		{
			sectorAngle = j * sectorStep;

			Vertex vertex;
			vertex.x = xy * cosf(sectorAngle);
			vertex.y = xy * sinf(sectorAngle);
			vertex.z = z;
			vertex.s = (float)j / sectors;
			vertex.t = (float)i / stacks;
			tmpVertices.push_back(vertex);
		}
	}

	clearVectors();

	Vertex v1, v2, v3, v4;
	int i, j, k, vi1, vi2;
	unsigned int index = 0;

	for (i = 0; i < stacks; i++)
	{
		vi1 = i * (sectors + 1);
		vi2 = (i + 1) * (sectors + 1);

		for (j = 0; j < sectors; j++, vi1++, vi2++)
		{
			v1 = tmpVertices[vi1];
			v2 = tmpVertices[vi2];
			v3 = tmpVertices[vi1 + 1];
			v4 = tmpVertices[vi2 + 1];

			if (i == 0)
			{
				addVertex(v1.x, v1.y, v1.z);
				addVertex(v2.x, v2.y, v2.z);
				addVertex(v4.x, v4.y, v4.z);

				addTexCoord(v1.s, v1.t);
				addTexCoord(v2.s, v2.t);
				addTexCoord(v4.s, v4.t);

				std::vector<float> N;
				N = CalcNormal(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v4.x, v4.y, v4.z
				);

				std::vector<float> BT = CalcTangent(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v4.x, v4.y, v4.z,
					v1.s, v1.t,
					v2.s, v2.t,
					v4.s, v4.t
				);

				for (k = 0; k < 3; k++)
				{
					addNormal(N[0], N[1], N[2]);
					addTangent(BT[0], BT[1], BT[2]);
					addBiTangent(BT[3], BT[4], BT[5]);
				}

				addIndices(index, index + 1, index + 2);

				index += 3;
			}
			else if (i == (stacks - 1))
			{
				addVertex(v1.x, v1.y, v1.z);
				addVertex(v2.x, v2.y, v2.z);
				addVertex(v3.x, v3.y, v3.z);

				addTexCoord(v1.s, v1.t);
				addTexCoord(v2.s, v2.t);
				addTexCoord(v3.s, v3.t);

				std::vector<float> N;
				N = CalcNormal(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z
				);

				std::vector<float> BT = CalcTangent(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z,
					v1.s, v1.t,
					v2.s, v2.t,
					v3.s, v3.t
				);

				for (k = 0; k < 3; k++)
				{
					addNormal(N[0], N[1], N[2]);
					addTangent(BT[0], BT[1], BT[2]);
					addBiTangent(BT[3], BT[4], BT[5]);
				}

				addIndices(index, index + 1, index + 2);

				index += 3;
			}
			else
			{
				addVertex(v1.x, v1.y, v1.z);
				addVertex(v2.x, v2.y, v2.z);
				addVertex(v3.x, v3.y, v3.z);
				addVertex(v4.x, v4.y, v4.z);

				addTexCoord(v1.s, v1.t);
				addTexCoord(v2.s, v2.t);
				addTexCoord(v3.s, v3.t);
				addTexCoord(v4.s, v4.t);

				std::vector<float> N;
				N = CalcNormal(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z
				);

				std::vector<float> BT = CalcTangent(
					v1.x, v1.y, v1.z,
					v2.x, v2.y, v2.z,
					v3.x, v3.y, v3.z,
					v1.s, v1.t,
					v2.s, v2.t,
					v3.s, v3.t
				);

				for (k = 0; k < 4; k++)
				{
					addNormal(N[0], N[1], N[2]);
					addTangent(BT[0], BT[1], BT[2]);
					addBiTangent(BT[3], BT[4], BT[5]);
				}

				addIndices(index, index + 1, index + 2);
				addIndices(index + 2, index + 1, index + 3);

				index += 4;
			}
		}
	}
	MakeInterleavedVertices();
	SetUp();
}

void Sphere::MakeVerticesSmooth()
{

	float x, y, z, s, t, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;

	float sectorStep = 2 * PI / sectors;
	float stackStep = PI / stacks;

	float sectorAngle, stackAngle;

	for (int i = 0; i <= stacks; i++)
	{
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);
		for (int j = 0; j <= sectors; j++)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			addVertex(x, y, z);

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			addNormal(nx, ny, nz);

			s = (float)j / sectors;
			t = (float)i / stacks;
			addTexCoord(s, t);
		}
	}

	int i, j;
	unsigned int k1, k2;
	for (i = 0; i < stacks; i++)
	{
		k1 = i * (sectors + 1);
		k2 = k1 + (sectors + 1);

		for (j = 0; j < sectors; j++, k1++, k2++)
		{
			if (i != 0)
			{
				addIndices(k1, k2, k1 + 1);
			}
			if (i != (stacks - 1))
			{
				addIndices(k1 + 1, k2, k2 + 1);
			}
		}
	}
	MakeInterleavedVertices();
	SetUp();
}

void Sphere::MakeInterleavedVertices()
{
	std::vector<float>().swap(InterleavedVertices);

	std::size_t i, j;
	std::size_t count = Vertices.size();

	for (i = 0, j = 0; i < count; i += 3, j += 2)
	{
		InterleavedVertices.push_back(Vertices[i]);
		InterleavedVertices.push_back(Vertices[i + 1]);
		InterleavedVertices.push_back(Vertices[i + 2]);

		InterleavedVertices.push_back(Normals[i]);
		InterleavedVertices.push_back(Normals[i + 1]);
		InterleavedVertices.push_back(Normals[i + 2]);

		InterleavedVertices.push_back(TexCoords[j]);
		InterleavedVertices.push_back(TexCoords[j + 1]);

		if (!smooth)
		{
			InterleavedVertices.push_back(Tangents[i]);
			InterleavedVertices.push_back(Tangents[i + 1]);
			InterleavedVertices.push_back(Tangents[i + 2]);

			InterleavedVertices.push_back(BiTangents[i]);
			InterleavedVertices.push_back(BiTangents[i + 1]);
			InterleavedVertices.push_back(BiTangents[i + 2]);

		}
	}
}

std::vector<float> Sphere::CalcNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	float EPSILON = 0.000001f;
	float nx, ny, nz;
	float e1x, e1y, e1z, e2x, e2y, e2z;
	std::vector<float> Normals(3, 0.0f);

	e1x = x2 - x1;
	e1y = y2 - y1;
	e1z = z2 - z1;
	e2x = x3 - x1;
	e2y = y3 - y1;
	e2z = z3 - z1;

	nx = e1y * e2z - e1z * e2y;
	ny = e1z * e2x - e1x * e2z;
	nz = e1x * e2y - e1y * e2x;

	float length = sqrtf(nx * nx + ny * ny + nz * nz);
	if (length > EPSILON)
	{
		float InvNorm = 1.0f / length;
		Normals[0] = nx * InvNorm;
		Normals[1] = ny * InvNorm;
		Normals[2] = nz * InvNorm;
	}
	return Normals;

}

std::vector<float> Sphere::CalcTangent(
	float x1, float y1, float z1, 
	float x2, float y2, float z2, 
	float x3, float y3, float z3,
	float uv1x, float uv1y,
	float uv2x, float uv2y,
	float uv3x, float uv3y

)
{
	std::vector<float> tmpTangents;
	float Tx, Ty, Tz, Bx, By, Bz;
	float e1x, e2x, e1y, e2y, e1z, e2z;
	float d1x, d2x, d1y, d2y;

	e1x = x2 - x1;
	e1y = y2 - y1;
	e1z = z2 - z1;
	e2x = x3 - x1;
	e2y	= y3 - y1;
	e2z	= z3 - z1;

	d1x = uv2x - uv1x;
	d1y = uv2y - uv1y;
	d2x = uv3x - uv1x;
	d2y = uv3y - uv1y;

	float r = 1.0f / (d1x * d2y - d2x * d1y);

	Tx = r * (d2y * e1x - d1y * e2x);
	Ty = r * (d2y * e1y - d1y * e2y);
	Tz = r * (d2y * e1z - d1y * e2z);

	tmpTangents.push_back(Tx);
	tmpTangents.push_back(Ty);
	tmpTangents.push_back(Tz);


	Bx = r *(-d2x * e1x + d1x * e2x);
	By = r *(-d2x * e1y + d1x * e2y);
	Bz = r *(-d2x * e1z + d1x * e2z);

	tmpTangents.push_back(Bx);
	tmpTangents.push_back(By);
	tmpTangents.push_back(Bz);

	return tmpTangents;
}

void Sphere::addVertex(float x1, float y1, float z1)
{
	Vertices.push_back(x1);
	Vertices.push_back(y1);
	Vertices.push_back(z1);
}

void Sphere::addNormal(float x, float y, float z)
{
	Normals.push_back(x);
	Normals.push_back(y);
	Normals.push_back(z);
}

void Sphere::addTangent(float x, float y, float z)
{
	Tangents.push_back(x);
	Tangents.push_back(y);
	Tangents.push_back(z);
}

void Sphere::addBiTangent(float x, float y, float z)
{
	BiTangents.push_back(x);
	BiTangents.push_back(y);
	BiTangents.push_back(z);
}

void Sphere::addTexCoord(float x, float y)
{
	TexCoords.push_back(x);
	TexCoords.push_back(y);
}

void Sphere::addIndices(unsigned int x, unsigned int y, unsigned int z)
{

	Indices.push_back(x);
	Indices.push_back(y);
	Indices.push_back(z);
}
