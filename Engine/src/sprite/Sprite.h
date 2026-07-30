#pragma once
#include "../entity/Entity2D.h"
#include "../vertex/Vertex.h"
#include "../animation/Animation.h"
#include "../textureImporter/TextureImporter.h"

#include "../EngineAPI.h"

using namespace std;

class Sprite : public Entity2D
{
private:

	void Init();

	Animation* animation;

	unsigned int texture;
	TextureImporter textureImporter;
	bool sharedTexture;

public:
	ENGINE_API Sprite();
	ENGINE_API ~Sprite();

	ENGINE_API void CreateTriangle(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1.0f));
	ENGINE_API void CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1.0f));
	ENGINE_API void SetSquareVertexColor(glm::vec4 colors[4]);
	ENGINE_API void SetTriangleVertexColor(glm::vec4 colors[4]);

	ENGINE_API void SetAnimation(Animation* animation);
	ENGINE_API Animation* GetAnimation();

	ENGINE_API void SetTexture(string path, int texWidth, int texHeight);
	ENGINE_API void SetTextureId(unsigned int textureId);
	ENGINE_API void SetSharedTexture(unsigned int textureId);
	ENGINE_API void SetTextureCoordinates(
		float topRightU,	float topRightV,
		float bottomRightU, float bottomRightV,
		float bottomLeftU,	float bottomLeftV,
		float topLeftU,		float topLeftV);
	unsigned int* GetTexture();

	int GetTextureWidth();
	int GetTextureHeight();

	bool UsesSharedTexture();

	ENGINE_API void Update() override;
	ENGINE_API void Draw() override;
};