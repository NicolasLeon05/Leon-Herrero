#include "Renderer.h"

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
