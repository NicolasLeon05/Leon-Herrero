#include "Sprite.h"

#include "../renderer/Renderer.h"

void Sprite::CreateSquare(Vertex one, Vertex two, Vertex three, Vertex four)
{
	verticesData.resize(36);
	indices.resize(6);

	verticesData[0] = one.GetPosX();
	verticesData[1] = one.GetPosY();
	verticesData[2] = one.GetPosZ();
	verticesData[3] = one.GetR();
	verticesData[4] = one.GetG();
	verticesData[5] = one.GetB();
	verticesData[6] = one.GetA();
	verticesData[7] = 0.0f;
	verticesData[8] = 1.0f;

	verticesData[9] = two.GetPosX();
	verticesData[10] = two.GetPosY();
	verticesData[11] = two.GetPosZ();
	verticesData[12] = two.GetR();
	verticesData[13] = two.GetG();
	verticesData[14] = two.GetB();
	verticesData[15] = two.GetA();
	verticesData[16] = 1.0f;
	verticesData[17] = 1.0f;

	verticesData[18] = three.GetPosX();
	verticesData[19] = three.GetPosY();
	verticesData[20] = three.GetPosZ();
	verticesData[21] = three.GetR();
	verticesData[22] = three.GetG();
	verticesData[23] = three.GetB();
	verticesData[24] = three.GetA();
	verticesData[25] = 0.0f;
	verticesData[26] = 0.0f;

	verticesData[27] = four.GetPosX();
	verticesData[28] = four.GetPosY();
	verticesData[29] = four.GetPosZ();
	verticesData[30] = four.GetR();
	verticesData[31] = four.GetG();
	verticesData[32] = four.GetB();
	verticesData[33] = four.GetA();
	verticesData[34] = 1.0f;
	verticesData[35] = 0.0f;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	if (!Renderer::IsInEntities(this))
	{
		Renderer::entities.push_back(this);
	}
}


void Sprite::Init()
{
	Renderer::InitSpriteBuffers(*this);
	GetMaterial().SetFilepath("Texture.shader");
	SetMaterial();
	GetMaterial().InitShader();

	std::cout << "Vertex" << std::endl;
	std::cout << GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << GetMaterial().GetFragmentSource() << std::endl;
}

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	for (int i = 0; i < Renderer::entities.size(); i++)
	{
		if (Renderer::entities[i] == this)
		{
			Renderer::entities.erase(Renderer::entities.begin() + i);
		}
	}
}

void Sprite::CreateTriangle(Vertex one, Vertex two, Vertex three)
{
	verticesData.resize(27);
	indices.resize(3);

	verticesData[0] = one.GetPosX();
	verticesData[1] = one.GetPosY();
	verticesData[2] = one.GetPosZ();
	verticesData[3] = one.GetR();
	verticesData[4] = one.GetG();
	verticesData[5] = one.GetB();
	verticesData[6] = one.GetA();
	verticesData[7] = one.GetS();
	verticesData[8] = one.GetT();

	verticesData[9] = two.GetPosX();
	verticesData[10] = two.GetPosY();
	verticesData[11] = two.GetPosZ();
	verticesData[12] = two.GetR();
	verticesData[13] = two.GetG();
	verticesData[14] = two.GetB();
	verticesData[15] = two.GetA();
	verticesData[16] = two.GetS();
	verticesData[17] = two.GetT();

	verticesData[18] = three.GetPosX();
	verticesData[19] = three.GetPosY();
	verticesData[20] = three.GetPosZ();
	verticesData[21] = three.GetR();
	verticesData[22] = three.GetG();
	verticesData[23] = three.GetB();
	verticesData[24] = three.GetA();
	verticesData[25] = three.GetS();
	verticesData[26] = three.GetT();

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	if (!Renderer::IsInEntities(this))
	{
		Renderer::entities.push_back(this);
	}

	Init();
}

void Sprite::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color)
{
	CreateTriangle(one, two, three);

	one.SetColor(color);
	two.SetColor(color);
	three.SetColor(color);

	Init();
}

void Sprite::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha)
{
	CreateTriangle(one, two, three);

	one.SetColor(color, alpha);
	two.SetColor(color, alpha);
	three.SetColor(color, alpha);

	Init();
}

void Sprite::CreateSquare(Vertex one, float width, float height)
{
	// one is the upper left side vertex
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), one.GetColor());
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), one.GetColor());
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), one.GetColor());

	CreateSquare(one, two, three, four);

	Init();
}

void Sprite::CreateSquare(Vertex one, float width, float height, Color color)
{
	// one is the upper left side vertex
	one.SetColor(color);
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color);
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color);
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color);

	CreateSquare(one, two, three, four);

	Init();
}

void Sprite::CreateSquare(Vertex one, float width, float height, Color color, float alpha)
{
	// one is the upper left side vertex
	one.SetColor(color, alpha);
	Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), color, alpha);
	Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), color, alpha);
	Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), color, alpha);

	CreateSquare(one, two, three, four);

	Init();
}

unsigned int* Sprite::GetTexture()
{
	return &texture;
}

void Sprite::SetTexturePath(string path)
{
	texturePath = path;
}

string Sprite::GetTexturePath()
{
	return texturePath;
}

void Sprite::Draw()
{
	GetMaterial().UseShader();
	Renderer::Draw(this, GetIndicesCount());
}
