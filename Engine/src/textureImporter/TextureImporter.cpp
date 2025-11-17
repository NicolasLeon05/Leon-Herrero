#include "TextureImporter.h"

void TextureImporter::SetTexture(std::string path, int texWidth, int texHeight)
{
	texturePath = path;
	textureWidth = texWidth;
	textureHeight = texHeight;
}
