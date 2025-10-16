#include "shape/Shape.h"
#include "renderer/Renderer.h"
#include "clock/Clock.h"
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


	glewInit();
	InitGame();

	Renderer::SetMvp(window);

	MyClock::InitClock();

	while (!window.ShouldClose())
	{
		Renderer::Clear();

		Update();

		MyClock::UpdateDeltaTime();

		Renderer::SwapBuffers(window);

		Renderer::PollEvents();
	}

	DeInitGame();

	for (int i = 0; i < Renderer::entities.size(); i++)
	{
		Renderer::entities[i]->GetMaterial().DeinitShader();
	}

	glfwTerminate();
	return 0;
}