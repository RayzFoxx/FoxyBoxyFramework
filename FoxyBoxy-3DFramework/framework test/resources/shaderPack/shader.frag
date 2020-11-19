#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D dTexture;

void main()
{
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
	FragColor = texture(dTexture, TexCoord);
};