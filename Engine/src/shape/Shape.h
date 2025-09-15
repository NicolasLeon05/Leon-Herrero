#pragma once
#include "../entity/Entity2D.h"
#include "ShapeType.h"
#include "../vertex/Vertex.h"


class Shape : public Entity2D
{
private:
	SHAPE_TYPE shapeType;

	void CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four);

public:
	Shape();
	Shape(SHAPE_TYPE shapeType);
	~Shape();

	void SetVertices(float posX, float posY, float posZ) override;

	//void CreateCircle();
	void CreateTriangle(Vertex one, Vertex two, Vertex three);
	void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color);
	void CreateSquare(Vertex one, float width, float height);
	void CreateSquare(Vertex one, float width, float height, Color color);
};