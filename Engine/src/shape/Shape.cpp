#include "Shape.h"

#include "../renderer/Renderer.h"

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
		 0.0f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, // top
		 0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, // bottom right
		-0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a // bottom left
	};
	indices =
	{
		0, 1, 2,
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
