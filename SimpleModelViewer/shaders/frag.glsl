#version 330 core

in vec4 MVPosition;
in vec3 Normal;
in vec3 LightPos;
in vec3 LightColor;
in vec2 TexCoord;

uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main()
{
	//Ambient
	float ambientStrength = 1.0f;
	vec3 ambient = ambientStrength * LightColor;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - vec3(MVPosition));
	vec3 diffuse = max(dot(norm, lightDir), 0.0f) * LightColor;

	//Specular
	float specularStrength = 1.0f;
	vec3 viewDir = normalize(-vec3(MVPosition));
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * LightColor;

	vec4 basicColor;
	
	if(textureSize(diffuseTexture, 0) == 1)
	{
		basicColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}
	else
	{
		basicColor = texture(diffuseTexture, TexCoord);
	}
	vec4 texColor = vec4(ambient + diffuse + specular, 1.0f) * basicColor;

	if(texColor.a < 0.1)
		discard;
	FragColor = texColor;
}