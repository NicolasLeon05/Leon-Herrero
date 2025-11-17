#include "Sprite.h"

#include "../renderer/Renderer.h"

//------------------------------------------------ PRIVATE -----------------------------------------------------

//void Sprite::CreateSquare(Vertex pos, float width, float height)
//{
//	//verticesData.resize(36);
//	//indices.resize(6);
//	//
//	//verticesData[0] = one.GetPosX();
//	//verticesData[1] = one.GetPosY();
//	//verticesData[2] = one.GetPosZ();
//	//verticesData[3] = one.GetR();
//	//verticesData[4] = one.GetG();
//	//verticesData[5] = one.GetB();
//	//verticesData[6] = one.GetA();
//	////verticesData[7] = 0.0f;
//	////verticesData[8] = 1.0f;
//	//verticesData[7] = animation.GetFrames()[0].frameCoords[0].u;
//	//verticesData[8] = animation.GetFrames()[0].frameCoords[0].v;
//	//
//	//verticesData[9] = two.GetPosX();
//	//verticesData[10] = two.GetPosY();
//	//verticesData[11] = two.GetPosZ();
//	//verticesData[12] = two.GetR();
//	//verticesData[13] = two.GetG();
//	//verticesData[14] = two.GetB();
//	//verticesData[15] = two.GetA();
//	////verticesData[16] = 1.0f;
//	////verticesData[17] = 1.0f;
//	//verticesData[16] = animation.GetFrames()[0].frameCoords[1].u;
//	//verticesData[17] = animation.GetFrames()[0].frameCoords[1].v;
//	//
//	//verticesData[18] = three.GetPosX();
//	//verticesData[19] = three.GetPosY();
//	//verticesData[20] = three.GetPosZ();
//	//verticesData[21] = three.GetR();
//	//verticesData[22] = three.GetG();
//	//verticesData[23] = three.GetB();
//	//verticesData[24] = three.GetA();
//	////verticesData[25] = 0.0f;
//	////verticesData[26] = 0.0f;
//	//verticesData[25] = animation.GetFrames()[0].frameCoords[2].u;
//	//verticesData[26] = animation.GetFrames()[0].frameCoords[2].v;
//	//
//	//verticesData[27] = four.GetPosX();
//	//verticesData[28] = four.GetPosY();
//	//verticesData[29] = four.GetPosZ();
//	//verticesData[30] = four.GetR();
//	//verticesData[31] = four.GetG();
//	//verticesData[32] = four.GetB();
//	//verticesData[33] = four.GetA();
//	////verticesData[34] = 1.0f;
//	////verticesData[35] = 0.0f;
//	//verticesData[34] = animation.GetFrames()[0].frameCoords[3].u;
//	//verticesData[35] = animation.GetFrames()[0].frameCoords[3].v;
//	//
//	//indices[0] = 0;
//	//indices[1] = 1;
//	//indices[2] = 2;
//	//indices[3] = 1;
//	//indices[4] = 3;
//	//indices[5] = 2;
//
//	verticesData = {
//	// position			/color					/ uv's
//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
//	 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
//	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
//	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top left 
//	};
//	indices = {  // note that we start from 0!
//		0, 1, 3,   // first triangle
//		1, 2, 3    // second triangle
//	};
//
//	if (!Renderer::IsInEntities(this))
//	{
//		Renderer::entities.push_back(this);
//	}
//}

void Sprite::Init()
{
	Renderer::InitSpriteBuffers(*this);
	GetMaterial().SetFilepath("Texture.shader");
	SetMaterial();
	GetMaterial().InitShader();

	//SetPosition(CalculateCenter().x, CalculateCenter().y, 0);
	//SetPosition(verticesData[0], verticesData[1], 0.0f);

	std::cout << "Vertex" << std::endl;
	std::cout << GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << GetMaterial().GetFragmentSource() << std::endl;
}

Sprite::Sprite()
{
	animation = new Animation();
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

	delete animation;
}


//------------------------------------------------ PUBLIC -----------------------------------------------------

void Sprite::CreateTriangle(glm::vec3 pos, float width, float height, glm::vec4 color)
{
	verticesData =
	{
		// position			/color								/ uv's
		 0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, 0.0f, 0.0f, // bottom left
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

//void Sprite::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color)
//{
//	CreateTriangle(one, two, three);
//
//	one.SetColor(color);
//	two.SetColor(color);
//	three.SetColor(color);
//
//	Init();
//}

//void Sprite::CreateTriangle(Vertex one, Vertex two, Vertex three, Color color, float alpha)
//{
//	CreateTriangle(one, two, three);
//
//	one.SetColor(color, alpha);
//	two.SetColor(color, alpha);
//	three.SetColor(color, alpha);
//
//	Init();
//}

void Sprite::CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color)
{
	// one is the upper left side vertex
	//Vertex two = Vertex(one.GetPosX() + width, one.GetPosY(), one.GetPosZ(), one.GetColor());
	//Vertex three = Vertex(one.GetPosX(), one.GetPosY() - height, one.GetPosZ(), one.GetColor());
	//Vertex four = Vertex(one.GetPosX() + width, one.GetPosY() - height, one.GetPosZ(), one.GetColor());

	verticesData =
	{
		// position			/color								/ uv's
		 0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, color.r, color.g, color.b, color.a, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, color.r, color.g, color.b, color.a, 0.0f, 1.0f  // top left 
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

void Sprite::SetSquareVertexColor(glm::vec4 colors[4])
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

void Sprite::SetTriangleVertexColor(glm::vec4 colors[4])
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


//void Sprite::CreateSquare(Vertex one, float width, float height, Color color)
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

//void Sprite::CreateSquare(Vertex one, float width, float height, Color color, float alpha)
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

void Sprite::SetAnimation(Animation* anim)
{
	anim->Reset();
	this->animation = anim;
}

unsigned int* Sprite::GetTexture()
{
	return &texture;
}

void Sprite::SetTexture(string path, int texWidth, int texHeight)
{
	texturePath = path;
	textureWidth = texWidth;
	textureHeight = texHeight;
	//animation.AddFrame(0, 0, textureWidth, textureHeight, textureWidth, textureHeight, 1);
}

string Sprite::GetTexturePath()
{
	return texturePath;
}

Animation* Sprite::GetAnimation()
{
	return animation;
}

int Sprite::GetTextureWidth()
{
	return textureWidth;
}

int Sprite::GetTextureHeight()
{
	return textureHeight;
}

void Sprite::Update()
{
	if (animation != nullptr)
	{
		animation->Update(); // actualiza el currentFrameIndex

		if (animation->HasFrameChanged())
		{
			int frameIndex = animation->GetCurrentFrameIndex();
			Frame frame = animation->GetFrames()[frameIndex];

			// Actualizamos solo los UVs
			verticesData[7] = frame.frameCoords[0].u;
			verticesData[8] = frame.frameCoords[0].v;

			verticesData[16] = frame.frameCoords[1].u;
			verticesData[17] = frame.frameCoords[1].v;

			verticesData[25] = frame.frameCoords[2].u;
			verticesData[26] = frame.frameCoords[2].v;

			verticesData[34] = frame.frameCoords[3].u;
			verticesData[35] = frame.frameCoords[3].v;

			Renderer::BindBuffers(*this);

			std::cout << "Frame Coords:" << std::endl;
			std::cout << "  0: (" << frame.frameCoords[0].u << ", " << frame.frameCoords[0].v << ")" << std::endl;
			std::cout << "  1: (" << frame.frameCoords[1].u << ", " << frame.frameCoords[1].v << ")" << std::endl;
			std::cout << "  2: (" << frame.frameCoords[2].u << ", " << frame.frameCoords[2].v << ")" << std::endl;
			std::cout << "  3: (" << frame.frameCoords[3].u << ", " << frame.frameCoords[3].v << ")" << std::endl;

		}

	}
}

void Sprite::Draw()
{
	GetMaterial().UseShader();
	Renderer::Draw(this, GetIndicesCount());
}
