#include "Renderer.h"
#include "../entity/Entity2D.h"

#include "gtc/type_ptr.hpp"

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

void Renderer::DrawShape(Entity2D& entity)
{
	unsigned int* VBO = entity.GetVBO();
	unsigned int* EBO = entity.GetEBO();
	unsigned int* VAO = entity.GetVAO();

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, entity.GetVerticesSize(),
		entity.GetVertices(), GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, entity.GetIndicesSize(),
		entity.GetIndices(), GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
}

void Renderer::PollEvents()
{
	glfwPollEvents();
}

void Renderer::Draw(Entity2D* entity, GLsizei count)
{
	//entity->Translate(0.0f, 0.0f, 0.0f);
	//entity->Rotate(0.0f, 0.0f, 0.0f);
	//entity->Scale(1.0f, 1.0f, 1.0f);

	unsigned int transformLoc = glGetUniformLocation(entity->GetMaterial().GetShader(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(entity->GetTRS()));

	glBindVertexArray(*entity->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
