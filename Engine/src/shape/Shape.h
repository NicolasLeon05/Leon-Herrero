#pragma once
#include "../entity/Entity2D.h"
#include "ShapeType.h"
#include "../vertex/Vertex.h"

#include "../EngineAPI.h"

class Shape : public Entity2D
{
private:
	void CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four);

	void Init();

public:
	ENGINE_API Shape();
	ENGINE_API ~Shape();

	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three);
	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color);
	ENGINE_API void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha);
	ENGINE_API void CreateSquare(Vertex one, float width, float height);
	ENGINE_API void CreateSquare(Vertex one, float width, float height, Color color);
	ENGINE_API void CreateSquare(Vertex one, float width, float height, Color color, float alpha);

	ENGINE_API void Draw() override;
};