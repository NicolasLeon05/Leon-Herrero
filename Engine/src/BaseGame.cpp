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

	Vertex v4 = Vertex(0.75f, 0.0f, 0.0f, Color::BLUE, 0.5f);
	Vertex v5 = Vertex(0.0f, 0.75f, 0.0f, Color::BLUE, 0.5f);
	Vertex v6 = Vertex(0.5f, 0.0f, 0.0f, Color::BLUE, 0.5f);

	Shape triangle2 = Shape();
	triangle2.CreateTriangle(v4, v5, v6); //Color::WHITE);

	float x = -0.7f;
	float y = -0.7f;
	float widht = 0.25f;
	float height = 0.25f;

	Vertex v7 = Vertex(x, y, 0.0f);

	Shape square = Shape();
	square.CreateSquare(v7, widht, height, Color::GREEN, 1.0f);

	shapes.push_back(triangle1);
	shapes.push_back(triangle2);
	shapes.push_back(square);

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

		if (shapes.size() > 0)

		shapes[0].Rotate(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < shapes.size(); i++)
		{
			shapes[i].GetMaterial().UseShader();
			Renderer::Draw(&shapes[i], 6);
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