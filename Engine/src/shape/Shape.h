#pragma once
#include "../entity/Entity2D.h"
#include "ShapeType.h"
#include "../vertex/Vertex.h"

#include "../EngineAPI.h"

class Shape : public Entity2D
{
private:

	void Init();

public:
	ENGINE_API Shape();
	ENGINE_API ~Shape();

	ENGINE_API void CreateTriangle(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1));
	ENGINE_API void CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color = glm::vec4(1));

	ENGINE_API void SetSquareVertexColor(glm::vec4 colors[4]);
	ENGINE_API void SetTriangleVertexColor(glm::vec4 colors[4]);

	ENGINE_API void Draw() override;
};