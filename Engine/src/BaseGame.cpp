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

	Vertex one = Vertex(-0.5f, 0.5f, 0.0f);
	Vertex two = Vertex(-0.5f, -0.5f, 0.0f);
	Vertex three = Vertex(0.0f, 0.5f, 0.0f);

	Shape triangle = Shape();
	triangle.CreateTriangle(one, two, three, Color::RED);

	Window window = Window(640, 480, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glewInit();

	triangle.Draw();

	triangle.GetMaterial().InitShader();

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		//game.Update();

		triangle.GetMaterial().UseShader();

		Renderer::Draw(GL_TRIANGLES, 0, 6);		

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	//game.DeInitGame();

	triangle.GetMaterial().DeinitShader();

	glfwTerminate();
	return 0;
}