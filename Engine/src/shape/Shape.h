#pragma once
#include "../entity/Entity2D.h"
#include "ShapeType.h"

class Shape : public Entity2D
{
private:
	SHAPE_TYPE shapeType;

public:
	Shape(SHAPE_TYPE shapeType);
	~Shape();

	void SetVertices(float posX, float posY, float posZ) override;
};