#pragma once
#include "../entity/Entity2D.h"
#include "../vertex/Vertex.h"

#include "../EngineAPI.h"

using namespace std;

class Sprite : public Entity2D
{
private:
	void CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four);

	void Init();

	unsigned int texture;

	string texturePath;
	int textureWidth;
	int textureHeight;

public:
	ENGINE_API Sprite();
	ENGINE_API ~Sprite();

	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three);
	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color);
	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha);
	ENGINE_API void CreateSquare(Vertex one, float width, float height);
	ENGINE_API void CreateSquare(Vertex one, float width, float height, Color color);
	ENGINE_API void CreateSquare(Vertex one, float width, float height, Color color, float alpha);

	unsigned int *GetTexture();
	ENGINE_API void SetTexture(string path, int texWidth, int texHeight);
	string GetTexturePath();

	int GetTextureWidth();
	int GetTextureHeight();

	ENGINE_API void Draw() override;
};