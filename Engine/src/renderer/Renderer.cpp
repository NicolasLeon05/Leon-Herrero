#include "Renderer.h"
#include "../entity/Entity2D.h"
#include "../shape/Shape.h"
#include "../sprite/Sprite.h"

#include "gtc/type_ptr.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <filesystem>

using namespace std::filesystem;

vector<Entity2D*> Renderer::entities;
glm::mat4 Renderer::mvp = glm::mat4(1.0f);

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::MakeContextCurrent(Window window)
{
	glfwMakeContextCurrent(window.GetGlfwWindow());
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::SwapBuffers(Window window)
{
	glfwSwapBuffers(window.GetGlfwWindow());
}
void Renderer::SetMVP(Window window)
{
	glm::mat4 view = lookAt(glm::vec3(0.0f, 0.0f, 10.0f), //Position
		glm::vec3(0.0f, 0.0f, 0.0f), //Target
		glm::vec3(0.0f, 1.0f, 0.0f)); //Transform Up
	glm::mat4 proj = glm::ortho(0.0f, float(window.GetWidth()), 0.0f, float(window.GetHeight()), -0.1f, 100.0f);

	mvp = proj * view;
}

bool Renderer::IsInEntities(Entity2D* entity)
{
	for (int i = 0; i < Renderer::entities.size(); i++)
	{
		if (Renderer::entities[i] == entity)
		{
			return true;
		}
	}

	return false;
}

void Renderer::GenBuffers(Entity2D& entity2D)
{
	glGenVertexArrays(1, entity2D.GetVAO());
	glGenBuffers(1, entity2D.GetVBO());
	glGenBuffers(1, entity2D.GetEBO());

	Sprite* sprite = dynamic_cast<Sprite*>(&entity2D);
	if (sprite != nullptr)
	{
		unsigned int* texture = sprite->GetTexture();
		glGenTextures(1, texture);
	}
}

void Renderer::BindBuffers(Entity2D& entity2D)
{
	glBindVertexArray(*entity2D.GetVAO());

	glBindBuffer(GL_ARRAY_BUFFER, *entity2D.GetVBO());
	glBufferData(GL_ARRAY_BUFFER, entity2D.GetVerticesSize(),
		entity2D.GetVertices(), GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *entity2D.GetEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, entity2D.GetIndicesSize(),
		entity2D.GetIndices(), GL_STREAM_DRAW);

	Sprite* sprite = dynamic_cast<Sprite*>(&entity2D);
	if (sprite != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, *sprite->GetTexture());
	}
}

void Renderer::InitShapeBuffers(Shape& shape)
{
	GenBuffers(shape);
	BindBuffers(shape);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
}

void Renderer::InitSpriteBuffers(Sprite& sprite)
{
	GenBuffers(sprite);
	BindBuffers(sprite);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 7));
	glEnableVertexAttribArray(2);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width = sprite.GetTextureWidth();
	int height = sprite.GetTextureHeight();
	int nrChannels = 0; //BUSCAR LA FORMA DE OBTENER LOS CANALES DE LA IMAGEN ANTES DE HACER stbi_load

	std::cout << "Trying to load texture from: " << sprite.GetTexturePath() << std::endl;
	std::cout << "Current working directory: " << current_path() << std::endl;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(sprite.GetTexturePath().c_str(), &width, &height, &nrChannels, 4);

	if (data)
	{
		cout << "Texture loaded succesfully" << endl;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
		cout << "stbi_failure_reason(): " << stbi_failure_reason() << endl;
	}
	stbi_image_free(data);
}

void Renderer::PollEvents()
{
	glfwPollEvents();
}

void Renderer::Draw(Shape* shape, GLsizei count)
{
	glm::mat4 model = shape->GetTRS();

	glm::mat4 mvpMatrix = mvp * model;

	glUniformMatrix4fv(glGetUniformLocation(shape->GetMaterial().GetShader(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	glBindVertexArray(*shape->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(Sprite* sprite, GLsizei count)
{
	glm::mat4 model = sprite->GetTRS();

	glm::mat4 mvpMatrix = mvp * model;

	glUniformMatrix4fv(glGetUniformLocation(sprite->GetMaterial().GetShader(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	glBindTexture(GL_TEXTURE_2D, *sprite->GetTexture());

	glBindVertexArray(*sprite->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
