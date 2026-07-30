#include "TextureImporter.h"

#include "GL/glew.h"
#include "../renderer/stb_image.h"

#include <iostream>

TextureImporter::TextureImporter()
{
	texture = 0;
	textureWidth = 0;
	textureHeight = 0;
}

TextureImporter::~TextureImporter()
{
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
}

bool TextureImporter::LoadTexture(std::string path, bool useNearestFilter)
{
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	texturePath = path;

	int channels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath.c_str(), &textureWidth, &textureHeight, &channels, 4);

	if (data == nullptr)
	{
		std::cout << "Failed to load texture: " << texturePath << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		return false;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int filter = useNearestFilter ? GL_NEAREST : GL_LINEAR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return true;
}

unsigned int TextureImporter::GetTexture()
{
	return texture;
}

int TextureImporter::GetTextureWidth()
{
	return textureWidth;
}

int TextureImporter::GetTextureHeight()
{
	return textureHeight;
}