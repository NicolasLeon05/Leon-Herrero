#include "Shape.h"

#include "../renderer/Renderer.h"

//void Shape::CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four)
//{
//	verticesData.resize(28);
//	indices.resize(6);
//
//	verticesData[0] = one.GetPosX();
//	verticesData[1] = one.GetPosY();
//	verticesData[2] = one.GetPosZ();
//	verticesData[3] = one.GetR();
//	verticesData[4] = one.GetG();
//	verticesData[5] = one.GetB();
//	verticesData[6] = one.GetA();
//
//	verticesData[7] = two.GetPosX();
//	verticesData[8] = two.GetPosY();
//	verticesData[9] = two.GetPosZ();
//	verticesData[10] = two.GetR();
//	verticesData[11] = two.GetG();
//	verticesData[12] = two.GetB();
//	verticesData[13] = two.GetA();
//
//	verticesData[14] = three.GetPosX();
//	verticesData[15] = three.GetPosY();
//	verticesData[16] = three.GetPosZ();
//	verticesData[17] = three.GetR();
//	verticesData[18] = three.GetG();
//	verticesData[19] = three.GetB();
//	verticesData[20] = three.GetA();
//
//	verticesData[21] = four.GetPosX();
//	verticesData[22] = four.GetPosY();
//	verticesData[23] = four.GetPosZ();
//	verticesData[24] = four.GetR();
//	verticesData[25] = four.GetG();
//	verticesData[26] = four.GetB();
//	verticesData[27] = four.GetA();
//
//	indices[0] = 0;
//	indices[1] = 1;
//	indices[2] = 2;
//	indices[3] = 2;
//	indices[4] = 3;
//	indices[5] = 1;
//
//	if (!Renderer::IsInEntities(this))
//	{
//		Renderer::entities.push_back(this);
//	}
//}


void Shape::Init()
{
	//translation = CalculateCenter();

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
	for (int i = 0; i < Renderer::entities.size(); i++)
	{
		if (Renderer::entities[i] == this)
		{
			Renderer::entities.erase(Renderer::entities.begin() + i);
		}
	}
}

void Shape::CreateTriangle(glm::vec3 pos, float width, float height, glm::vec4 color)
{
	verticesData =
	{
		// position			/color								
		 0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, // top right
		 0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, // bottom right
		-0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a // bottom left
	};
	indices =
	{  // note that we start from 0!
		0, 1, 2,   // first triangle
	};

	if (!Renderer::IsInEntities(this))
	{
		Renderer::entities.push_back(this);
	}

	Init();
	SetScale(width, height, 1.0f);
	SetPosition(pos.x, pos.y, pos.z);
}

//void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color)
//{
//	CreateTriangle(one, two, three);
//
//	one.SetColor(color);
//	two.SetColor(color);
//	three.SetColor(color);
//
//	Init();
//}

//void Shape::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha)
//{
//	CreateTriangle(one, two, three);
//
//	one.SetColor(color, alpha);
//	two.SetColor(color, alpha);
//	three.SetColor(color, alpha);
//
//	Init();
//}

void Shape::CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color)
{
	// one is the upper left side vertex
	//Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), one.GetColor());
	//Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), one.GetColor());
	//Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), one.GetColor());

	verticesData =
	{
		// position			/color							
		 0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, // top right
		 0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, // bottom right
		-0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, // bottom left
		-0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a // top left 
	};
	indices =
	{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	if (!Renderer::IsInEntities(this))
	{
		Renderer::entities.push_back(this);
	}

	Init();
	SetScale(width, height, 1.0f);
	SetPosition(pos.x, pos.y, pos.z);
}

//void Shape::CreateSquare(Vertex one, float width, float height, Color color)
//{
//	// one is the upper left side vertex
//	one.SetColor(color);
//	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color);
//	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color);
//	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color);
//
//	CreateSquare(one, two, three, four);
//
//	Init();
//}

//void Shape::CreateSquare(Vertex one, float width, float height, Color color, float alpha)
//{
//	// one is the upper left side vertex
//	one.SetColor(color, alpha);
//	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color, alpha);
//	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color, alpha);
//	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color, alpha);
//
//	CreateSquare(one, two, three, four);
//
//	Init();
//}

void Shape::SetSquareVertexColor(glm::vec4 colors[4])
{
	verticesData[3] = colors[0].r;
	verticesData[4] = colors[0].g;
	verticesData[5] = colors[0].b;
	verticesData[6] = colors[0].a;

	verticesData[12] = colors[1].r;
	verticesData[13] = colors[1].g;
	verticesData[14] = colors[1].b;
	verticesData[15] = colors[1].a;

	verticesData[21] = colors[2].r;
	verticesData[22] = colors[2].g;
	verticesData[23] = colors[2].b;
	verticesData[24] = colors[2].a;

	verticesData[30] = colors[3].r;
	verticesData[31] = colors[3].g;
	verticesData[32] = colors[3].b;
	verticesData[33] = colors[3].a;
}

void Shape::SetTriangleVertexColor(glm::vec4 colors[4])
{
	verticesData[3] = colors[0].r;
	verticesData[4] = colors[0].g;
	verticesData[5] = colors[0].b;
	verticesData[6] = colors[0].a;

	verticesData[12] = colors[1].r;
	verticesData[13] = colors[1].g;
	verticesData[14] = colors[1].b;
	verticesData[15] = colors[1].a;

	verticesData[21] = colors[2].r;
	verticesData[22] = colors[2].g;
	verticesData[23] = colors[2].b;
	verticesData[24] = colors[2].a;
}

void Shape::Draw()
{
	GetMaterial().UseShader();
	Renderer::Draw(this, GetIndicesCount());
}
