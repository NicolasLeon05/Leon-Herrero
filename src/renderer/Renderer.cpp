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

void Renderer::DrawEntity(Entity2D& entity)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, entity.GetVerticesSize(),
		entity.GetVertices(), GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

void Renderer::PollEvents()
{
	glfwPollEvents();
}

void Renderer::DrawArrays()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
