#include "entity/Entity2D.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include "BaseGame.h"

#include <fstream>
#include <sstream>
#include <string>


int main(void)
{
	Entity2D entity2D = Entity2D();

	Window window = Window(640, 480, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glewInit();

	entity2D.Draw();

	entity2D.GetMaterial().InitShader();

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		Renderer::DrawArrays(GL_TRIANGLES, 0, 3);

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	entity2D.GetMaterial().DeinitShader();

	glfwTerminate();
	return 0;
}