#pragma once
#include "../entity/Entity2D.h"
#include "../vertex/Vertex.h"
#include "../animation/Animation.h"

#include "../EngineAPI.h"

using namespace std;

class Sprite : public Entity2D
{
private:

	void Init();

	Animation* animation;

	unsigned int texture;
	string texturePath;
	int textureWidth;
	int textureHeight;

public:
	ENGINE_API Sprite();
	ENGINE_API ~Sprite();

	ENGINE_API void CreateTriangle(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1));
	ENGINE_API void CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1));
	ENGINE_API void SetSquareVertexColor(glm::vec4 colors[4]);
	ENGINE_API void SetTriangleVertexColor(glm::vec4 colors[4]);

	ENGINE_API void SetAnimation(Animation* animation);
	unsigned int *GetTexture();

	ENGINE_API void SetTexture(string path, int texWidth, int texHeight);
	string GetTexturePath();
	ENGINE_API Animation* GetAnimation();

	int GetTextureWidth();
	int GetTextureHeight();

	ENGINE_API void Update() override;

	ENGINE_API void Draw() override;
};