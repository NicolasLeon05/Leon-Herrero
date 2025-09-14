#include "shape/Shape.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include "BaseGame.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int BaseGame::RunEngine()
{
	//BaseGame game = BaseGame();

	vector<Shape> shapes;

	Vertex v1 = Vertex(-0.25f, 0.0f, 0.0f, Color::BLUE);
	Vertex v2 = Vertex(0.0f, -0.5f, 0.0f, Color::GREEN);
	Vertex v3 = Vertex(-0.5f, 0.0f, 0.0f, Color::WHITE);

	Shape triangle1 = Shape();
	triangle1.CreateTriangle(v1, v2, v3); //Color::WHITE);

	Vertex v4 = Vertex(0.75f, 0.0f, 0.0f, Color::GREEN);
	Vertex v5 = Vertex(0.0f, 0.75f, 0.0f, Color::WHITE);
	Vertex v6 = Vertex(0.5f, 0.0f, 0.0f, Color::RED);

	Shape triangle2 = Shape();
	triangle2.CreateTriangle(v4, v5, v6); //Color::WHITE);	

	Window window = Window(640, 480, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glewInit();

	triangle1.Draw();
	triangle2.Draw();

	triangle1.GetMaterial().InitShader();
	triangle2.GetMaterial().InitShader();

	shapes.push_back(triangle1);
	shapes.push_back(triangle2);

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		//game.Update();

		triangle1.GetMaterial().UseShader();

		for  (int i = 0; i < shapes.size(); i++)
		{
			Renderer::Draw(&shapes[i], 3);
		}


		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	//game.DeInitGame();

	triangle1.GetMaterial().DeinitShader();
	triangle2.GetMaterial().DeinitShader();

	glfwTerminate();
	return 0;
}