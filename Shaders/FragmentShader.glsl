#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 lightPosOut;
in vec3 viewPosOut;

in mat3 TBN;

uniform sampler2D walltext;
uniform sampler2D walltextnorm;
uniform int Divisions;

void main()
{
	vec3 lightDir = normalize(lightPosOut - FragPos);
	vec3 viewDir = normalize(viewPosOut - FragPos);
	vec3 color = texture(walltext, TexCoords * Divisions).rgb;

	vec3 normal;
	normal = texture(walltextnorm, TexCoords * Divisions).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	//normal = normalize(TBN * normal);

	vec3 lightColor = vec3(0.5, 0.5, 0.5);

	float ambientstr = 0.2;
	vec3 ambient  = ambientstr * color;

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	float specularstr = 0.1;
	vec3 halwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halwayDir, normal),0.0),1.0);
	vec3 specular = spec * vec3(0.1);

	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(result, 1.0);
}
