#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aModelMatrix;
layout (location = 7) in vec3 aColor;
layout (location = 8) in float aSpec;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool Instance;

out vec3 Normal;
out vec3 FragPos;
out vec3 inColor;
out float Spec;

void main()
{
	mat4 modelInst = aModelMatrix;
	if(!Instance)
	{
		FragPos = vec3(model * vec4(aPos, 1.0));
		Normal = mat3(transpose(inverse(model))) * aNormal;
		gl_Position = projection * view * model * vec4(aPos, 1.0);
		inColor = vec3(1.0,1.0,1.0);
		Spec = 1.0;
	}
	else 
	{
		FragPos = vec3(modelInst * vec4(aPos, 1.0));
		Normal = mat3(transpose(inverse(modelInst))) * aNormal;
		gl_Position = projection * view * modelInst * vec4(aPos, 1.0);
		inColor = aColor;
		Spec = aSpec;
	}
}
