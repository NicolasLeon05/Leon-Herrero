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

int BaseGame::RunEngine(Window window)
{
	if (!glfwInit())
		return -1;


	window.CreateWindow();

	Renderer::MakeContextCurrent(window);

	glm::mat4 view = lookAt(glm::vec3(0.0f, 0.0f, 0.1f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::ortho(0.0f, float(window.GetWidth()), 0.0f, float(window.GetHeight()), -0.1f, 100.0f);

	glm::mat4 mvp = proj * view;

	glewInit();
	InitGame();

	//for (int i = 0; i < Renderer::shapes.size(); i++)
	//{
	//	Renderer::shapes[i]->Draw();
	//	Renderer::shapes[i]->GetMaterial().InitShader();
	//}

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		Update();

		for (int i = 0; i < Renderer::shapes.size(); i++)
		{
			//Renderer::shapes[i]->GetMaterial().UseShader();
			Renderer::shapes[i]->GetMaterial().SetProjection("mvp", mvp);
			//Renderer::Draw(Renderer::shapes[i], 6);
		}

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	DeInitGame();

	for (int i = 0; i < Renderer::shapes.size(); i++)
	{
		Renderer::shapes[i]->GetMaterial().DeinitShader();
	}

	glfwTerminate();
	return 0;
}