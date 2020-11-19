#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 aLightPos;
out vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 inv;
uniform vec3 lightPos;
uniform vec3 lightCol;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	ourColor = aColor;
	Normal = mat3(transpose(inv)) * aNormal;
	lightColor = lightCol;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
};