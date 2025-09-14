#include "Renderer.h"
#include "../entity/Entity2D.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::MakeContextCurrent(Window window)
{
	glfwMakeContextCurrent(window.GetGlfwWindow());
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
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

	glVertexAttribPointer(1, 4,GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);
}


void Renderer::PollEvents()
{
	glfwPollEvents();
}

void Renderer::Draw(Entity2D* entity,GLsizei count)
{
	glBindVertexArray(*entity->GetVAO());
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
