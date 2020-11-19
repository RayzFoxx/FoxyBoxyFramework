#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

class Texture
{
public:
	unsigned int ID;
	Texture(const char* texturePath, unsigned int wrapS, unsigned int wrapT, unsigned int minF, unsigned int magF)
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magF);

		textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);
		if (textureData)
		{
			switch (nrChannels)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
				glGenerateMipmap(GL_TEXTURE_2D);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
				glGenerateMipmap(GL_TEXTURE_2D);
				break;
			}
		}
		else
		{
			std::cout << "Unable to generate texture from: " << texturePath << std::endl;
		}

		stbi_image_free(textureData);
	}

	void activate(unsigned int atlasNum)
	{
		glActiveTexture(GL_TEXTURE0 + atlasNum);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

private:
	int width, height, nrChannels;
	unsigned char* textureData;
};

#endif
