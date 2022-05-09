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
uniform sampler2D walltextdepth;
uniform int Divisions;

uniform float height_scale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
	vec3 lightDir = normalize(lightPosOut - FragPos);
	vec3 viewDir = normalize(viewPosOut - FragPos);
	vec2 Tex_Coords = ParallaxMapping(TexCoords , viewDir);

	if(Tex_Coords.x > 1.0 * Divisions || Tex_Coords.y > 1.0 * Divisions || Tex_Coords.x < 0.0 || Tex_Coords.y < 0.0)
	{
		discard;
	}

	vec3 color = texture(walltext, Tex_Coords * Divisions).rgb;

	vec3 normal;
	//normal = normalize(Normal);
	normal = texture(walltextnorm, Tex_Coords * Divisions).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 lightColor = vec3(0.5, 0.5, 0.5);

	float ambientstr = 0.2;
	vec3 ambient  = ambientstr * color;

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	float specularstr = 0.5;
	vec3 halwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halwayDir, normal),0.0),128.0);
	vec3 specular = spec * vec3(0.2);

	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(result, 1.0);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	const float minLayers = 8;
	const float maxLayers = 128;
	float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0,0.0,1.0), viewDir)));
	float layerDepth = 1.0 / numLayers;
	float currentLayerDepth = 0.0;
	vec2 P = viewDir.xy / viewDir.z * height_scale;
	vec2 deltaTexCoords = P / numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(walltextdepth, currentTexCoords * Divisions).r;

	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(walltextdepth, currentTexCoords * Divisions).r;
		currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(walltextdepth, prevTexCoords * Divisions).r - currentLayerDepth + layerDepth;


	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}
