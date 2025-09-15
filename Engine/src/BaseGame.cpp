#include "shape/Shape.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

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
	Vertex v5 = Vertex(0.0f, 0.75f, 0.0f, Color::RED);
	Vertex v6 = Vertex(0.5f, 0.0f, 0.0f, Color::RED);

	Shape triangle2 = Shape();
	triangle2.CreateTriangle(v4, v5, v6); //Color::WHITE);

	shapes.push_back(triangle1);
	shapes.push_back(triangle2);

	Window window = Window(640, 480, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glewInit();

	for (int i = 0; i < shapes.size(); i++)
	{
		shapes[i].Draw();
		shapes[i].GetMaterial().InitShader();
	}

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		//game.Update();

		shapes[0].GetMaterial().UseShader();

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