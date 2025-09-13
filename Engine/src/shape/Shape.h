#pragma once
#include "../entity/Entity2D.h"
#include "ShapeType.h"
#include "../vertex/Vertex.h"


class Shape : public Entity2D
{
private:
	SHAPE_TYPE shapeType;

public:
	Shape();
	Shape(SHAPE_TYPE shapeType);
	~Shape();

	void SetVertices(float posX, float posY, float posZ) override;

	//void CreateCircle();
	void CreateTriangle(Vertex one, Vertex two, Vertex three);
	void CreateTriangle(Vertex one, Vertex two, Vertex three, Color color);
	//void CreateSquare();
};