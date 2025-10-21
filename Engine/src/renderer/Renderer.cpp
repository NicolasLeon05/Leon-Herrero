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
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
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
	glm::mat4 view = lookAt(glm::vec3(0.0f, 0.0f, 0.1f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::ortho(0.0f, float(window.GetWidth()), 0.0f, float(window.GetHeight()), -0.1f, 100.0f);

	mvp = proj * view ;
}

void Renderer::UpdateMVP(Entity2D* entity)
{	
	glm::mat4 model = entity->GetTRS();

	mvp *= model;
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

void Renderer::InitShapeBuffers(Shape& shape)
{
	unsigned int* VBO = shape.GetVBO();
	unsigned int* EBO = shape.GetEBO();
	unsigned int* VAO = shape.GetVAO();

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, shape.GetVerticesSize(),
		shape.GetVertices(), GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.GetIndicesSize(),
		shape.GetIndices(), GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
}

void Renderer::InitSpriteBuffers(Sprite& sprite)
{
	unsigned int* VBO = sprite.GetVBO();
	unsigned int* EBO = sprite.GetEBO();
	unsigned int* VAO = sprite.GetVAO();

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sprite.GetVerticesSize(),
		sprite.GetVertices(), GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sprite.GetIndicesSize(),
		sprite.GetIndices(), GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 7));
	glEnableVertexAttribArray(2);

	unsigned int* texture = sprite.GetTexture();
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *sprite.GetTexture());

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
	UpdateMVP(shape);

	glUniformMatrix4fv(glGetUniformLocation(shape->GetMaterial().GetShader(), "mvp"), 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(*shape->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(Sprite* sprite, GLsizei count)
{
	UpdateMVP(sprite);

	glUniformMatrix4fv(glGetUniformLocation(sprite->GetMaterial().GetShader(), "mvp"), 1, GL_FALSE, &mvp[0][0]);

	glBindTexture(GL_TEXTURE_2D, *sprite->GetTexture());

	glBindVertexArray(*sprite->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
