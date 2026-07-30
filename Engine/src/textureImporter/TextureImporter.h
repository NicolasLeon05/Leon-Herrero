#pragma once

#include <string>

class TextureImporter
{
private:
	unsigned int texture;
	std::string texturePath;
	int textureWidth;
	int textureHeight;

public:
	TextureImporter();
	~TextureImporter();

	bool LoadTexture(std::string path, bool useNearestFilter = false);

	unsigned int GetTexture();

	int GetTextureWidth();
	int GetTextureHeight();
};