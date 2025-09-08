#include "shape/Shape.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include "BaseGame.h"

#include <fstream>
#include <sstream>
#include <string>

int BaseGame::RunEngine()
{
	//BaseGame game = BaseGame();

	Shape entity2D = Shape(SHAPE_TYPE::SQUARE);
	entity2D.SetVertices(0.5f, 0.5f, 0.0f);

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

		//game.Update();

		Renderer::Draw(GL_TRIANGLES, 0, 6);		

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	//game.DeInitGame();

	entity2D.GetMaterial().DeinitShader();

	glfwTerminate();
	return 0;
}