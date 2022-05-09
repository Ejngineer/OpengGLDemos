#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangents;
layout (location = 4) in vec3 aBiTangents;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform vec3 lightPos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 viewPosOut;
out vec3 lightPosOut;
out int NormalMapOut;
out mat3 TBN;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(mat3(model) * aTangents);
	vec3 B = normalize(mat3(model) * aBiTangents);
	vec3 N = normalize(mat3(model) * aNormal);
	//vec3 B = cross(T,N);
	//T = normalize(T - dot(T, N) * N);
	
	TBN = transpose(mat3(T,B,N));
	Normal = normalMatrix * aNormal;

	FragPos = TBN * vec3(model * vec4(aPos, 1.0));
	viewPosOut = TBN * viewPos;
	lightPosOut = TBN * lightPos;
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);

}
