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
	float sWidht = 0.25f;
	float sHeight = 0.25f;

	Vertex v7 = Vertex(x, y, 0.0f);

	Shape square = Shape();
	square.CreateSquare(v7, sWidht, sHeight, Color::GREEN, 1.0f);

	int width = 640;
	int height = 480;

	Window window = Window(width, height, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glm::ortho(0.0f, float(width), 0.0f, float(height), 0.1f, 100.0f);

	glewInit();

	for (int i = 0; i < Renderer::shapes.size(); i++)
	{
		Renderer::shapes[i]->Draw();
		Renderer::shapes[i]->GetMaterial().InitShader();
	}

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		//game.Update();

		if (Renderer::shapes.size() > 0)
		{
			Renderer::shapes[0]->Rotate(0.0f, 0.0f, 1.0f);
		}

		for (int i = 0; i < Renderer::shapes.size(); i++)
		{
			Renderer::shapes[i]->GetMaterial().UseShader();
			Renderer::Draw(Renderer::shapes[i], 6);
		}

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	//game.DeInitGame();

	for (int i = 0; i < Renderer::shapes.size(); i++)
	{
		Renderer::shapes[i]->GetMaterial().DeinitShader();
	}

	glfwTerminate();
	return 0;
}