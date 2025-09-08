#include "Shape.h"

Shape::Shape(SHAPE_TYPE shapeType)
{
	this->shapeType = shapeType;

	switch (this->shapeType)
	{
	case SHAPE_TYPE::POINT:
	{
		vertices.resize(3);
		indices.resize(1);
		break;
	}

	case SHAPE_TYPE::LINE:
	{
		vertices.resize(6);
		indices.resize(2);
		break;
	}

	case SHAPE_TYPE::TRIANGLE:
	{
		vertices.resize(9);
		indices.resize(3);
		break;
	}

	case SHAPE_TYPE::SQUARE:
	{
		vertices.resize(12);
		indices.resize(6);
		break;
	}

	default:
	{
		this->shapeType = SHAPE_TYPE::TRIANGLE;
		vertices.resize(9);
		indices.resize(3);
		break;
	}
	}
}

Shape::~Shape()
{
}

void Shape::SetVertices(float posX, float posY, float posZ)
{
	switch (shapeType)
	{
	//Empty
	case SHAPE_TYPE::POINT:
	{
	
		break;
	}
	//Empty
	case SHAPE_TYPE::LINE:
	{
	
		break;
	}
	
	case SHAPE_TYPE::TRIANGLE:
	{
		vertices[0] = posX;
		vertices[1] = posY;
		vertices[2] = posZ;
		vertices[3] = posX;
		vertices[4] = -posY;
		vertices[5] = posZ;
		vertices[6] = -posX;
		vertices[7] = -posY;
		vertices[8] = posZ;
	
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		break;
	}
	
	case SHAPE_TYPE::SQUARE:
	{
		vertices[0] = -posX;
		vertices[1] = -posY;
		vertices[2] = posZ;
		vertices[3] = posX;
		vertices[4] = -posY;
		vertices[5] = posZ;
		vertices[6] = posX;
		vertices[7] = posY;
		vertices[8] = posZ;
		vertices[9] = -posX;
		vertices[10] = posY;
		vertices[11] = posZ;
	
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;
		break;
	}
	
	default:
	{
		std::cout << std::endl << "SHAPE default entered. Something went wrong" << std::endl;
		break;
	}
	}
}
