#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 aLightPos;
in vec3 lightColor;

uniform sampler2D dTexture;

void main()
{
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(aLightPos - TexCoord);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec4 result = vec4(1.0) + diffuse;
	FragColor = texture(dTexture, TexCoord) * result;
};