#include "Sprite.h"

#include "../renderer/Renderer.h"

//------------------------------------------------ PRIVATE -----------------------------------------------------

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

void Sprite::CreateSquare(glm::vec3 pos, float width, float height, glm::vec4 color)
{
	// one is the upper left side vertex
	
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
