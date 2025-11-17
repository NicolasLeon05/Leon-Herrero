#pragma once

#include <string>

class TextureImporter
{
private:
	std::string texturePath;
	int textureWidth;
	int textureHeight;

public:
	void SetTexture(std::string path, int texWidth, int texHeight);
};