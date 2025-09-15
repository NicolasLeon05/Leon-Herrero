#include "Shape.h"

void Shape::CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four)
{
	verticesData[0] = one.GetPosX();
	verticesData[1] = one.GetPosY();
	verticesData[2] = one.GetPosZ();
	verticesData[3] = one.GetR();
	verticesData[4] = one.GetG();
	verticesData[5] = one.GetB();
	verticesData[6] = one.GetA();

	verticesData[7] = two.GetPosX();
	verticesData[8] = two.GetPosY();
	verticesData[9] = two.GetPosZ();
	verticesData[10] = two.GetR();
	verticesData[11] = two.GetG();
	verticesData[12] = two.GetB();
	verticesData[13] = two.GetA();

	verticesData[14] = three.GetPosX();
	verticesData[15] = three.GetPosY();
	verticesData[16] = three.GetPosZ();
	verticesData[17] = three.GetR();
	verticesData[18] = three.GetG();
	verticesData[19] = three.GetB();
	verticesData[20] = three.GetA();

	verticesData[21] = four.GetPosX();
	verticesData[22] = four.GetPosY();
	verticesData[23] = four.GetPosZ();
	verticesData[24] = four.GetR();
	verticesData[25] = four.GetG();
	verticesData[26] = four.GetB();
	verticesData[27] = four.GetA();

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 1;
}

Shape::Shape()
{
	shapeType = SHAPE_TYPE::TRIANGLE;
}

Shape::Shape(SHAPE_TYPE shapeType)
{
	this->shapeType = shapeType;

	switch (this->shapeType)
	{
	case SHAPE_TYPE::POINT:
	{
		verticesData.resize(3);
		indices.resize(1);
		break;
	}

	case SHAPE_TYPE::LINE:
	{
		verticesData.resize(6);
		indices.resize(2);
		break;
	}

	case SHAPE_TYPE::TRIANGLE:
	{
		verticesData.resize(9);
		indices.resize(3);
		break;
	}

	case SHAPE_TYPE::SQUARE:
	{
		verticesData.resize(12);
		indices.resize(6);
		break;
	}

	default:
	{
		this->shapeType = SHAPE_TYPE::TRIANGLE;
		verticesData.resize(9);
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
		verticesData[0] = posX;
		verticesData[1] = posY;
		verticesData[2] = posZ;
		verticesData[3] = posX;
		verticesData[4] = -posY;
		verticesData[5] = posZ;
		verticesData[6] = -posX;
		verticesData[7] = -posY;
		verticesData[8] = posZ;

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		break;
	}

	case SHAPE_TYPE::SQUARE:
	{
		verticesData[0] = -posX;
		verticesData[1] = -posY;
		verticesData[2] = posZ;
		verticesData[3] = posX;
		verticesData[4] = -posY;
		verticesData[5] = posZ;
		verticesData[6] = posX;
		verticesData[7] = posY;
		verticesData[8] = posZ;
		verticesData[9] = -posX;
		verticesData[10] = posY;
		verticesData[11] = posZ;

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

void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three)
{
	verticesData.resize(21);
	indices.resize(3);

	verticesData[0] = one.GetPosX();
	verticesData[1] = one.GetPosY();
	verticesData[2] = one.GetPosZ();
	verticesData[3] = one.GetR();
	verticesData[4] = one.GetG();
	verticesData[5] = one.GetB();
	verticesData[6] = one.GetA();

	verticesData[7] = two.GetPosX();
	verticesData[8] = two.GetPosY();
	verticesData[9] = two.GetPosZ();
	verticesData[10] = two.GetR();
	verticesData[11] = two.GetG();
	verticesData[12] = two.GetB();
	verticesData[13] = two.GetA();

	verticesData[14] = three.GetPosX();
	verticesData[15] = three.GetPosY();
	verticesData[16] = three.GetPosZ();
	verticesData[17] = three.GetR();
	verticesData[18] = three.GetG();
	verticesData[19] = three.GetB();
	verticesData[20] = three.GetA();

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
}

void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color)
{
	CreateTriangle(one, two, three);

	one.SetColor(color);
	two.SetColor(color);
	three.SetColor(color);
}

void Shape::CreateSquare(Vertex one, float width, float height)
{
	verticesData.resize(28);
	indices.resize(6);

	// one is the upper left side vertex
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), one.GetColor());
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), one.GetColor());
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), one.GetColor());

	CreateSquare(one, two, three, four);
}

void Shape::CreateSquare(Vertex one, float width, float height, Color color)
{
	verticesData.resize(28);
	indices.resize(6);

	// one is the upper left side vertex
	one.SetColor(color);
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color);
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color);
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color);

	CreateSquare(one, two, three, four);
}
