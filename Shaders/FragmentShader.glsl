#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 inColor;
uniform vec3 lightPosition;

void main()
{
	vec3 Color = inColor;
	vec3 lightColor = vec3(0.5, 0.5, 0.5);
	vec3 lightPos = lightPosition;
	vec3 normal = normalize(Normal);

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);

	float ambientstr = 0.2;
	vec3 ambient = ambientstr * lightColor;

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec= pow(max(dot(viewDir, reflectDir),0.0),16.0);

	//vec3 halfwayDir = normalize(viewDir + lightDir);
	//float spec = pow(max(dot(halfwayDir, normal),0.0),64.0);
	
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * Color;

	FragColor = vec4(result, 1.0);
	//FragColor = vec4(Color, 1.0);
}
