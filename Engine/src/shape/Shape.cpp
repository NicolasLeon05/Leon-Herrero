#include "Shape.h"

#include "../renderer/Renderer.h"

void Shape::CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four)
{
	verticesData.resize(28);
	indices.resize(6);

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

	if (!Renderer::IsInShapes(this))
	{
		Renderer::shapes.push_back(this);
	}
}


void Shape::Init()
{
	Renderer::InitShapeBuffers(*this);
	GetMaterial().SetFilepath("Basic.shader");
	SetMaterial();
	GetMaterial().InitShader();

	std::cout << "Vertex" << std::endl;
	std::cout << GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << GetMaterial().GetFragmentSource() << std::endl;
}

Shape::Shape()
{

}

Shape::~Shape()
{
	for (int i = 0; i < Renderer::shapes.size(); i++)
	{
		if (Renderer::shapes[i] == this)
		{
			Renderer::shapes.erase(Renderer::shapes.begin() + i);
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

	if (!Renderer::IsInShapes(this))
	{
		Renderer::shapes.push_back(this);
	}

	Init();
}

void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color)
{
	CreateTriangle(one, two, three);

	one.SetColor(color);
	two.SetColor(color);
	three.SetColor(color);

	Init();
}

void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha)
{
	CreateTriangle(one, two, three);

	one.SetColor(color, alpha);
	two.SetColor(color, alpha);
	three.SetColor(color, alpha);

	Init();
}

void Shape::CreateSquare(Vertex one, float width, float height)
{
	// one is the upper left side vertex
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), one.GetColor());
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), one.GetColor());
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), one.GetColor());

	CreateSquare(one, two, three, four);

	Init();
}

void Shape::CreateSquare(Vertex one, float width, float height, Color color)
{
	// one is the upper left side vertex
	one.SetColor(color);
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color);
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color);
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color);

	CreateSquare(one, two, three, four);

	Init();
}

void Shape::CreateSquare(Vertex one, float width, float height, Color color, float alpha)
{
	// one is the upper left side vertex
	one.SetColor(color, alpha);
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color, alpha);
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color, alpha);
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color, alpha);

	CreateSquare(one, two, three, four);

	Init();
}

void Shape::Draw()
{
	GetMaterial().UseShader();
	Renderer::Draw(this, GetIndicesCount());
}
